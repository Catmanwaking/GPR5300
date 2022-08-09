#pragma once
#include <xutility>
#include "D3D.h"
#include "Utils.h"
#include <vector>
#include <d3dcompiler.h>

#pragma comment(lib, "dxgi.lib")

INT D3D::Init(HWND hWnd, UINT width, UINT height, BOOL windowed)
{
	INT error = 0;
	DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;	

	error = CreateSwapChain(hWnd, width, height, windowed, format);
	if (error) return error;
	error = CreateRenderTargetView();
	if (error) return error;
	error = CreateDepthStencilView(width, height);
	if (error) return error;
	error = CreateRasterizerState();
	if (error) return error;
	error = CreateInputLayout();
	if (error) return error;

	D3D11_VIEWPORT viewPort = {};
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;
	viewPort.Width = (FLOAT)width;
	viewPort.Height = (FLOAT)height;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;

	pD3DDeviceContext->OMSetRenderTargets(1, &pRenderTargetView, pDepthStencilView);
	pD3DDeviceContext->RSSetViewports(1, &viewPort);
	pD3DDeviceContext->RSSetState(pRasterizerState);

	return 0;
}

void D3D::BeginScene()
{
	FLOAT backGround[4] = { 0.3f, 0.3f, 0.3f, 1.0f };
	pD3DDeviceContext->ClearRenderTargetView(pRenderTargetView, backGround);
	pD3DDeviceContext->IASetInputLayout(pInputLayout);
}

void D3D::EndScene()
{
	pSwapChain->Present(0, 0);
}

void D3D::DeInit()
{
	SafeRelease<ID3D11InputLayout>(pInputLayout);
	SafeRelease<ID3D11RenderTargetView>(pRenderTargetView);
	SafeRelease<IDXGISwapChain>(pSwapChain);
	SafeRelease<ID3D11DeviceContext>(pD3DDeviceContext);
	SafeRelease<ID3D11Device>(pD3DDevice);
}

INT D3D::CreateSwapChain(HWND hWnd, UINT width, UINT height, BOOL windowed, DXGI_FORMAT format)
{
	DXGI_USAGE usage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	DXGI_SWAP_EFFECT swapEffect = DXGI_SWAP_EFFECT_DISCARD;
	D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_HARDWARE;
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};
	D3D_FEATURE_LEVEL usedFeatureLevel = {};

	DXGI_SWAP_CHAIN_DESC swapChainDescription = {};
	swapChainDescription.OutputWindow = hWnd;
	swapChainDescription.Windowed = windowed;
	swapChainDescription.BufferCount = 1;
	swapChainDescription.BufferDesc.Width = width;
	swapChainDescription.BufferDesc.Height = height;
	//swapChainDescription.BufferDesc.RefreshRate = 0;
	swapChainDescription.BufferDesc.Format = format;
	swapChainDescription.BufferUsage = usage;
	swapChainDescription.SwapEffect = swapEffect;
	swapChainDescription.SampleDesc.Count = 1;
	HRESULT hr = D3D11CreateDeviceAndSwapChain
	(
		nullptr, driverType, nullptr, 0,
		featureLevels, std::size(featureLevels),
		D3D11_SDK_VERSION, &swapChainDescription,
		&pSwapChain, &pD3DDevice,
		&usedFeatureLevel, &pD3DDeviceContext
	);
	if (FAILED(hr)) return 20;
	return 0;
}

INT D3D::CreateRenderTargetView()
{
	ID3D11Texture2D* pBackBufferTexture = nullptr;
	HRESULT hr = pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBufferTexture));
	if (FAILED(hr)) return 22;
	hr = pD3DDevice->CreateRenderTargetView(pBackBufferTexture, nullptr, &pRenderTargetView);
	if (FAILED(hr)) return 24;
	SafeRelease<ID3D11Texture2D>(pBackBufferTexture);
	return 0;
}

INT D3D::CreateDepthStencilView(UINT width, UINT height)
{
	ID3D11Texture2D* pDepthStencilViewTexture = nullptr;
	D3D11_TEXTURE2D_DESC depthStencilViewTextureDesc = {};
	depthStencilViewTextureDesc.Width = width;
	depthStencilViewTextureDesc.Height = height;
	depthStencilViewTextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilViewTextureDesc.ArraySize = 1;
	depthStencilViewTextureDesc.SampleDesc.Count = 1;
	HRESULT hr = pD3DDevice->CreateTexture2D(&depthStencilViewTextureDesc, nullptr, &pDepthStencilViewTexture);
	if (FAILED(hr)) return 26;
	hr = pD3DDevice->CreateDepthStencilView(pDepthStencilViewTexture, nullptr, &pDepthStencilView);
	if (FAILED(hr)) return 28;
	SafeRelease<ID3D11Texture2D>(pDepthStencilViewTexture);
	return 0;
}

INT D3D::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC rasterizerDesc = {};
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_BACK;
	rasterizerDesc.FrontCounterClockwise = FALSE;
	HRESULT hr = pD3DDevice->CreateRasterizerState(&rasterizerDesc, &pRasterizerState);
	if (FAILED(hr)) return 21;
	return 0;
}

INT D3D::CreateInputLayout()
{
	ID3DBlob* pCompiledShaderCode = nullptr;
	HRESULT hr = D3DReadFileToBlob(TEXT("BaseVertexShader.cso"), &pCompiledShaderCode);
	if (FAILED(hr)) return 23;
	D3D11_INPUT_ELEMENT_DESC elementDescription[5] = {};
	elementDescription[0].SemanticName = "POSITION";
	elementDescription[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	elementDescription[1].SemanticName = "NORMAL";
	elementDescription[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	elementDescription[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	elementDescription[2].SemanticName = "TEXCOORD";
	elementDescription[2].Format = DXGI_FORMAT_R32G32_FLOAT;
	elementDescription[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	elementDescription[3].SemanticName = "TANGENT";
	elementDescription[3].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	elementDescription[3].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	elementDescription[4].SemanticName = "BINORMAL";
	elementDescription[4].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	elementDescription[4].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	hr = pD3DDevice->CreateInputLayout
	(
		elementDescription,
		std::size(elementDescription),
		pCompiledShaderCode->GetBufferPointer(),
		pCompiledShaderCode->GetBufferSize(),
		&pInputLayout
	);
	SafeRelease<ID3DBlob>(pCompiledShaderCode);
	if (FAILED(hr)) return 25;

	return 0;
}

INT D3D::GetDisplayModes(DXGI_FORMAT format)
{
	UINT numModes = 0;
	IDXGIFactory* pFactory = nullptr;
	IDXGIAdapter* pAdapter = nullptr;
	IDXGIOutput* pOutput = nullptr;
	DXGI_MODE_DESC* pDisplayModes = nullptr;
	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**) &pFactory);
	if (FAILED(hr)) return 101;
	hr = pFactory->EnumAdapters(0, &pAdapter);
	if (FAILED(hr)) return 102;
	hr = pAdapter->EnumOutputs(0, &pOutput);
	if (FAILED(hr)) return 103;
	hr = pOutput->GetDisplayModeList(format, 0, &numModes, NULL);
	if (FAILED(hr)) return 104;
	pDisplayModes = new DXGI_MODE_DESC[numModes];
	hr = pOutput->GetDisplayModeList(format, 0, &numModes, pDisplayModes);
	if (FAILED(hr)) return 105;
	
	//get preferred mode

	delete[] pDisplayModes;
	pDisplayModes = nullptr;
	SafeRelease<IDXGIFactory>(pFactory);
	SafeRelease<IDXGIAdapter>(pAdapter);
	SafeRelease<IDXGIOutput>(pOutput);
	return 0;
}
