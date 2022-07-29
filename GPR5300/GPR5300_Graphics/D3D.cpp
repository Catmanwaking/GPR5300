#pragma once
#include "D3D.h"
#include "Utils.h"

#pragma comment(lib, "d3d9.lib")

INT D3D::Init(HWND hWnd, UINT width, UINT height, BOOL windowed)
{
	UINT adapter = D3DADAPTER_DEFAULT;
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

	pD3D->GetAdapterDisplayMode(adapter, &mode);

	D3DPRESENT_PARAMETERS d3dpp = {};
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = windowed;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = windowed ? width : mode.Width;
	d3dpp.BackBufferHeight = windowed ? height : mode.Height;
	d3dpp.BackBufferFormat = mode.Format;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	d3dpp.FullScreen_RefreshRateInHz = windowed ? 0 : mode.RefreshRate;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	
	hr = pD3D->CreateDevice(adapter, devType, hWnd, vertexProcessing, &d3dpp, &pD3DDevice);
	if (FAILED(hr))
		return 24;

	pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	SafeRelease<IDirect3D9>(pD3D);

	return 0;
}

void D3D::BeginScene()
{
	pD3DDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(60, 60, 60), 1.0f, 0xffffffff);

	pD3DDevice->BeginScene();
}

void D3D::EndScene()
{
	pD3DDevice->EndScene();

	pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
}

void D3D::DeInit()
{
	SafeRelease<IDirect3DDevice9>(pD3DDevice);
}
