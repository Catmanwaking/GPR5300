#pragma once
#include <xutility>
#include "D3D.h"
#include "Utils.h"

INT D3D::Init(HWND hWnd, UINT width, UINT height, BOOL windowed)
{
	DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;
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
	HRESULT hr;

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

	hr = D3D11CreateDeviceAndSwapChain
	(
		nullptr, driverType, nullptr, 0,
		featureLevels, std::size(featureLevels),
		D3D11_SDK_VERSION, &swapChainDescription,
		&pDXGISwapChain, &pD3DDevice,
		&usedFeatureLevel, &pD3DDeviceContext
	);
	if (FAILED(hr)) return 20;

	ID3D11Texture2D* pBackBufferTexture = nullptr;
	hr = pDXGISwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBufferTexture));
	if (FAILED(hr)) return 22;

	hr = pD3DDevice->CreateRenderTargetView(pBackBufferTexture, nullptr, &pRenderTargetView);
	if (FAILED(hr)) return 24;
	SafeRelease<ID3D11Texture2D>(pBackBufferTexture);

	D3D11_VIEWPORT viewPort = {};
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;
	viewPort.Width = width;
	viewPort.Height = height;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;

	D3D11_RASTERIZER_DESC rasterizerDesc = {};
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_NONE;
	rasterizerDesc.FrontCounterClockwise = FALSE;

	hr = pD3DDevice->CreateRasterizerState(&rasterizerDesc, &pRasterizerState);
	if (FAILED(hr)) return 29;

	//D3DDISPLAYMODE mode = {};
	//pD3D->GetAdapterDisplayMode(adapter, &mode);

	//d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	//d3dpp.FullScreen_RefreshRateInHz = windowed ? 0 : mode.RefreshRate;
	//d3dpp.EnableAutoDepthStencil = TRUE;
	//d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	pD3DDeviceContext->OMSetRenderTargets(1, &pRenderTargetView, nullptr);
	pD3DDeviceContext->RSSetViewports(1, &viewPort);
	pD3DDeviceContext->RSSetState(pRasterizerState);

	//SafeRelease<IDirect3D9>(pD3D);

	return 0;
}

void D3D::BeginScene()
{
	FLOAT backGround[4] = { 0.3f, 0.3f, 0.3f, 1.0f };
	pD3DDeviceContext->ClearRenderTargetView(pRenderTargetView, backGround);
}

void D3D::EndScene()
{
	pDXGISwapChain->Present(0, 0);
}

void D3D::DeInit()
{
	SafeRelease<ID3D11RenderTargetView>(pRenderTargetView);
	SafeRelease<IDXGISwapChain>(pDXGISwapChain);
	SafeRelease<ID3D11DeviceContext>(pD3DDeviceContext);
	SafeRelease<ID3D11Device>(pD3DDevice);
}
