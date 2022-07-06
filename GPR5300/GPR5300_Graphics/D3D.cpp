#pragma once
#include "D3D.h"

#pragma comment(lib, "d3d9.lib")

INT D3D::Init(HWND hWnd, UINT width, UINT height, BOOL windowed)
{
	UINT adapter = D3DADAPTER_DEFAULT;
	D3DFORMAT format = D3DFMT_A8R8G8B8;
	D3DDEVTYPE devType = D3DDEVTYPE_HAL;

	IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (pD3D == nullptr)
		return 20;

	D3DCAPS9 d3dCaps = {};
	HRESULT hr = pD3D->GetDeviceCaps(adapter, devType, &d3dCaps);
	if (FAILED(hr))
		return 22;

	DWORD vertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	if (d3dCaps.VertexProcessingCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;

	D3DDISPLAYMODE mode = {};
	UINT modeCount = pD3D->GetAdapterModeCount(adapter, format);
	pD3D->EnumAdapterModes(adapter, format, modeCount, &mode);	

	D3DPRESENT_PARAMETERS d3dpp = {};
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = windowed;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.BackBufferFormat = format;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	d3dpp.FullScreen_RefreshRateInHz = windowed ? 0 : mode.RefreshRate;
	
	hr = pD3D->CreateDevice(adapter, devType, hWnd, vertexProcessing, &d3dpp, &pD3DDevice);
	if (FAILED(hr))
		return 24;

	pD3D->Release();

	return 0;
}

void D3D::BeginScene()
{
	pD3DDevice->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 0, 255), 1.0f, 0xffffffff);

	pD3DDevice->BeginScene();
}

void D3D::EndScene()
{
	pD3DDevice->EndScene();

	pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

void D3D::DeInit()
{
	if (pD3DDevice != nullptr)
	{
		pD3DDevice->Release();
		pD3DDevice = nullptr;
	}
}
