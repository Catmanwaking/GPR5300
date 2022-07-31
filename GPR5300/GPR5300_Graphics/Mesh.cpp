#include "Mesh.h"
#include "Vertex.h"
#include "Utils.h"
#include "MeshLoader.h"

using namespace DirectX;
using namespace Constants;

INT Mesh::Init(ID3D11Device* pD3DDevice, std::string path)
{
	INT error = 0;

	pMeshData = MeshLoader::LoadFromFile(path);

	error = InitVertexBuffer(pD3DDevice);
	if (error) return error;

	error = InitIndexBuffer(pD3DDevice);
	if (error) return error;

	if (!pMeshData->materialFileName.empty())
	{
		error = material.Init(pD3DDevice, pMeshData->materialFileName);
		if (error) return error;
	}

	pMeshData->DeInit();
	pMeshData = nullptr;

	return 0;
}

void Mesh::Render(ID3D11DeviceContext* pD3DDeviceContext, const XMMATRIX& rViewProjectionMatrix)
{
	material.Render(pD3DDeviceContext, pTransform->GetTransformationMatrix(), rViewProjectionMatrix);

	static UINT offset = 0;
	pD3DDeviceContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &vertexStride, &offset);
	pD3DDeviceContext->IASetIndexBuffer(pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	pD3DDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pD3DDeviceContext->DrawIndexed(indexCount, 0, 0);
}

void Mesh::DeInit()
{
	SafeRelease<ID3D11Buffer>(pVertexBuffer);
	SafeRelease<ID3D11Buffer>(pIndexBuffer);
}

INT Mesh::InitVertexBuffer(ID3D11Device* pD3DDevice)
{
	vertexCount = pMeshData->vertexCount;
	vertexStride = sizeof(Vertex);

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.ByteWidth = vertexCount * vertexStride;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;

	D3D11_SUBRESOURCE_DATA subResourceData = {};
	subResourceData.pSysMem = pMeshData->vertices->data();

	HRESULT hr = pD3DDevice->CreateBuffer(&bufferDesc, &subResourceData, &pVertexBuffer);
	if (FAILED(hr)) return 30;

	return 0;
}

INT Mesh::InitIndexBuffer(ID3D11Device* pD3DDevice)
{
	indexCount = pMeshData->indexCount;

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.ByteWidth = indexCount * sizeof(USHORT);
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;

	D3D11_SUBRESOURCE_DATA subResourceData = {};
	subResourceData.pSysMem = pMeshData->indices->data();

	HRESULT hr = pD3DDevice->CreateBuffer(&bufferDesc, &subResourceData, &pIndexBuffer);
	if (FAILED(hr)) return 32;

	return 0;
}
