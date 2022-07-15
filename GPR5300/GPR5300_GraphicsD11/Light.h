#pragma once
#include <d3d9.h>

class Light
{
public:
	INT Init(D3DLIGHT9& light, DWORD id);
	void Render(IDirect3DDevice9* pD3DDevice);
	void DeInit();

private:
	D3DLIGHT9 light = {};
	DWORD id = 0;
};

