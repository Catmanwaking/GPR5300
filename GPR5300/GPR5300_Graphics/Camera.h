#pragma once
#include <d3d9.h>
#include "GameObject.h"
#include "IUpdateable.h"

class Camera : public GameObject, public IUpdateable
{
public:
	INT Init(IDirect3DDevice9* pD3DDevice, UINT screenWidth, UINT screenHeight);
	virtual void Update();
	virtual void DeInit();

private:
	D3DMATRIX viewMatrix = {};
	D3DMATRIX projectionMatrix = {};
};

