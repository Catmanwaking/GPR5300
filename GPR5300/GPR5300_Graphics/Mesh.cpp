#include <DirectXMath.h>
#include "Mesh.h"
#include "Vertex.h"
#include "Utils.h"
#include "MeshLoader.h"

using namespace DirectX;
using namespace Constants;

INT Mesh::Init(IDirect3DDevice9* pD3DDevice, std::string path)
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

void Mesh::Render(IDirect3DDevice9* pD3DDevice)
{
	material.Render(pD3DDevice);

	XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(&transformMatrix), pTransform->GetTransformationMatrix());

	pD3DDevice->SetTransform(D3DTS_WORLD, &transformMatrix);

	pD3DDevice->SetFVF(FVF);
	pD3DDevice->SetStreamSource(0, pVertexBuffer, 0, vertexStride);
	pD3DDevice->SetIndices(pIndexBuffer);
	pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexCount, 0, indexCount / 3);
}

void Mesh::DeInit()
{
	SafeRelease<IDirect3DVertexBuffer9>(pVertexBuffer);
	SafeRelease<IDirect3DIndexBuffer9>(pIndexBuffer);
}

INT Mesh::InitVertexBuffer(IDirect3DDevice9* pD3DDevice)
{
	vertexCount = pMeshData->vertexCount;
	vertexStride = sizeof(Vertex);

	HRESULT hr = pD3DDevice->CreateVertexBuffer
	(
		vertexCount * vertexStride,
		D3DUSAGE_WRITEONLY,
		FVF,
		D3DPOOL_MANAGED,
		&pVertexBuffer,
		nullptr
	);
	if (FAILED(hr)) return 30;

	Vertex* vertices = nullptr;
	hr = pVertexBuffer->Lock(0, 0, reinterpret_cast<void**>(&vertices), 0);
	if (FAILED(hr)) return 32;

	for (size_t i = 0; i < vertexCount; i++)
		vertices[i] = pMeshData->vertices->at(i);

	hr = pVertexBuffer->Unlock();
	if (FAILED(hr)) return 34;

	vertices = nullptr;

	return 0;
}

INT Mesh::InitIndexBuffer(IDirect3DDevice9* pD3DDevice)
{
	indexCount = pMeshData->indexCount;

	HRESULT hr = pD3DDevice->CreateIndexBuffer(indexCount * sizeof(USHORT), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pIndexBuffer, nullptr);
	if (FAILED(hr)) return 40;

	USHORT* indices = nullptr;
	hr = pIndexBuffer->Lock(0, 0, reinterpret_cast<void**>(&indices), 0);
	if (FAILED(hr)) return 42;

	for (USHORT i = 0; i < indexCount; i++) //TODO why does a breakpoint here break the program?
		indices[i] = pMeshData->indices->at(i);

	hr = pIndexBuffer->Unlock();
	if (FAILED(hr)) return 44;

	indices = nullptr;

	return 0;
}
