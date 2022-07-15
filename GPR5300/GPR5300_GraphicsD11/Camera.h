#pragma once
#include <d3d9.h>

class Camera
{
public:
	INT Init(IDirect3DDevice9* pD3DDevice, UINT screenWidth, UINT screenHeight);
	void Update();
	void DeInit();

private:
	D3DMATRIX viewMatrix = {};
	D3DMATRIX projectionMatrix = {};
};

