#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "GameObject.h"
#include "IRenderable.h"
#include "Material.h"
#include "MeshData.h"

using namespace DirectX;

class Mesh : public Component, public IRenderable
{
public:
	INT Init(ID3D11Device* pD3DDevice, std::string fileName);
	virtual void Render(ID3D11DeviceContext* pD3DDeviceContext, const XMMATRIX& viewProjectionMatrix);
	virtual void DeInit();

private:
	INT InitVertexBuffer(ID3D11Device* pD3DDevice);
	INT InitIndexBuffer(ID3D11Device* pD3DDevice);

	Material material = {};

	ID3D11Buffer* pVertexBuffer = nullptr;
	ID3D11Buffer* pIndexBuffer = nullptr;

	USHORT vertexCount = 0;
	UINT vertexStride = 0;
	UINT indexCount = 0;

	XMMATRIX transformMatrix = {};

	MeshData* pMeshData = nullptr;
};

