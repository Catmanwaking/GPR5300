#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

class Mesh
{
public:
	INT Init(ID3D11Device* pD3DDevice);
	void Update();
	void Render(ID3D11DeviceContext* pD3DDeviceContext);
	void DeInit();

private:
	INT InitVertexBuffer(ID3D11Device* pD3DDevice);
	INT InitIndexBuffer(ID3D11Device* pD3DDevice);

	ID3D11Buffer* pVertexBuffer = nullptr;
	ID3D11Buffer* pIndexBuffer = nullptr;

	USHORT vertexCount = 0;
	UINT vertexStride = 0;
	UINT indexCount = 0;

	XMFLOAT4X4 transformMatrix = {};
};

