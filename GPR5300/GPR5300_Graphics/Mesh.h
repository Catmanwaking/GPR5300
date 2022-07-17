#pragma once
#include <d3d9.h>
#include "GameObject.h"
#include "IRenderable.h"

class Mesh : public Component, public IRenderable
{
public:
	INT Init(IDirect3DDevice9* pD3DDevice);
	virtual void Render(IDirect3DDevice9* pD3DDevice);
	virtual void DeInit();

private:
	INT InitVertexBuffer(IDirect3DDevice9* pD3DDevice);
	INT InitIndexBuffer(IDirect3DDevice9* pD3DDevice);

	IDirect3DVertexBuffer9* pVertexBuffer = nullptr;
	IDirect3DIndexBuffer9* pIndexBuffer = nullptr;

	USHORT vertexCount = 0;
	UINT vertexStride = 0;
	UINT indexCount = 0;

	D3DMATRIX transformMatrix = {};
};

