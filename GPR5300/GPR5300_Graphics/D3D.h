#pragma once
#include <d3d9.h>

class D3D
{
public:
	INT Init(HWND hWnd, UINT width, UINT height, BOOL windowed);
	void BeginScene();
	void EndScene();
	void DeInit();

	IDirect3DDevice9* GetDevice() { return pD3DDevice; }

private:
	IDirect3DDevice9* pD3DDevice = nullptr;
};

