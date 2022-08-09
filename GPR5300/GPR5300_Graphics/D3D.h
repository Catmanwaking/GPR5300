#pragma once
#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")

class D3D
{
public:
	INT Init(HWND hWnd, UINT width, UINT height, BOOL windowed);
	void BeginScene();
	void EndScene();
	void DeInit();

	ID3D11Device* GetDevice() { return pD3DDevice; }
	ID3D11DeviceContext* GetDeviceContext() { return pD3DDeviceContext; }
	//IDXGISwapChain* GetSwapChain() { return pSwapChain; }
	//ID3D11RenderTargetView* GetRenderTargetView() { return pRenderTargetView; }
	ID3D11DepthStencilView* GetDepthStencilView() { return pDepthStencilView; }

private:
	ID3D11Device* pD3DDevice = nullptr;
	ID3D11DeviceContext* pD3DDeviceContext = nullptr;
	IDXGISwapChain* pSwapChain = nullptr;
	ID3D11RenderTargetView* pRenderTargetView = nullptr;
	ID3D11DepthStencilView* pDepthStencilView = nullptr;
	ID3D11RasterizerState* pRasterizerState = nullptr;
	ID3D11InputLayout* pInputLayout;

	INT CreateSwapChain(HWND hWnd, UINT width, UINT height, BOOL windowed, DXGI_FORMAT format);
	INT CreateRenderTargetView();
	INT CreateDepthStencilView(UINT width, UINT height);
	INT CreateRasterizerState();
	INT CreateInputLayout();

	INT GetDisplayModes(DXGI_FORMAT format);
};

