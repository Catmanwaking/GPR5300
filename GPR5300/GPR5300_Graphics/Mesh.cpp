#include <DirectXMath.h>
#include "Mesh.h"
#include "Vertex.h"
#include "Utils.h"

using namespace DirectX;
using namespace Constants;

INT Mesh::Init(IDirect3DDevice9* pD3DDevice)
{
	INT error = 0;

	error = InitVertexBuffer(pD3DDevice);
	if (error != 0)
		return error;

	error = InitIndexBuffer(pD3DDevice);
	if (error != 0)
		return error;

	return 0;
}

INT Mesh::AddMaterial(IDirect3DDevice9* pD3DDevice, LPCTSTR path)
{
	return material.Init(pD3DDevice, path);;
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
	vertexCount = 4;
	vertexStride = sizeof(Vertex);

	HRESULT hr = pD3DDevice->CreateVertexBuffer
	(
		vertexCount * vertexStride,
		D3DUSAGE_WRITEONLY,
		FVF,//D3DFVF
		D3DPOOL_MANAGED,
		&pVertexBuffer,
		nullptr
	);
	if (FAILED(hr))
		return 30;

	Vertex* vertices = nullptr;
	hr = pVertexBuffer->Lock(0, 0, reinterpret_cast<void**>(&vertices), 0);
	if (FAILED(hr))
		return 32;

	vertices[0] = Vertex(-0.5f,  0.5f, 0.0f, 0.0f, 0.0f);
	vertices[1] = Vertex( 0.5f,  0.5f, 0.0f, 1.0f, 0.0f);
	vertices[2] = Vertex( 0.5f, -0.5f, 0.0f, 1.0f, 1.0f);
	vertices[3] = Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 1.0f);

	hr = pVertexBuffer->Unlock();
	if (FAILED(hr))
		return 34;

	vertices = nullptr;

	return 0;
}

INT Mesh::InitIndexBuffer(IDirect3DDevice9* pD3DDevice)
{
	indexCount = 6;

	HRESULT hr = pD3DDevice->CreateIndexBuffer(indexCount * sizeof(USHORT), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pIndexBuffer, nullptr);
	if (FAILED(hr))
		return 40;

	USHORT* indices = nullptr;
	hr = pIndexBuffer->Lock(0, 0, reinterpret_cast<void**>(&indices), 0);
	if (FAILED(hr))
		return 42;

	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 2; indices[5] = 3;

	hr = pIndexBuffer->Unlock();
	if (FAILED(hr))
		return 44;

	indices = nullptr;

	return 0;
}
