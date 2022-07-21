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

	ID3D11Device* GetDevice() const { return pD3DDevice; }
	ID3D11DeviceContext* GetDeviceContext() const { return pD3DDeviceContext; }
	//IDXGISwapChain* GetSwapChain() { return pDXGISwapChain; }
	//ID3D11RenderTargetView* GetRenderTargetView() { return pRenderTargetView; }

private:
	ID3D11Device* pD3DDevice = nullptr;
	ID3D11DeviceContext* pD3DDeviceContext = nullptr;
	IDXGISwapChain* pDXGISwapChain = nullptr;
	ID3D11RenderTargetView* pRenderTargetView = nullptr;
};

