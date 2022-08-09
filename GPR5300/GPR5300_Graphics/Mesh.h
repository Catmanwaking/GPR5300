#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "GameObject.h"
#include "IRenderable.h"
#include "Material.h"
#include "MeshLoaderData.h"
#include "Shaders.h"
#include "MeshGenerator.h"

using namespace DirectX;
using namespace Shaders;

class Mesh : public Component, public IRenderable
{
public:
	virtual INT Init(ID3D11Device* pD3DDevice, std::string fileName, Shader shader);
	virtual INT Init(ID3D11Device* pD3DDevice, MeshGenerator::Shape shape, Shader shader);
	virtual void Render(ID3D11DeviceContext* pD3DDeviceContext, const XMMATRIX& viewProjectionMatrix);
	virtual void DeInit();

protected:
	INT InitVertexBuffer(ID3D11Device* pD3DDevice);
	INT InitIndexBuffer(ID3D11Device* pD3DDevice);

	ID3D11Buffer* pVertexBuffer = nullptr;
	ID3D11Buffer* pIndexBuffer = nullptr;

	USHORT vertexCount = 0;
	UINT vertexStride = 0;
	UINT indexCount = 0;

	XMMATRIX transformMatrix = {};

	MeshLoaderData* pMeshData = nullptr;

private:
	Material material = {};
};

