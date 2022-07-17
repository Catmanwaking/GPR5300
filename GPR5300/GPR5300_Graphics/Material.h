#pragma once
#include <d3d9.h>

class Material
{
public:
	INT Init(IDirect3DDevice9* pD3DDevice, LPCTSTR texturePath);
	void Render(IDirect3DDevice9* pD3DDevice);
	void DeInit();

private:
	IDirect3DTexture9* pTexture = nullptr;
	D3DMATERIAL9 material = {};
};

