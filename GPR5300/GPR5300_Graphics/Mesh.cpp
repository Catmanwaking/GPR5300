#include <DirectXMath.h>
#include "Mesh.h"
#include "Vertex.h"
#include "Utils.h"

using namespace DirectX;

INT Mesh::Init(IDirect3DDevice9* pD3DDevice)
{
	INT error = 0;

	error = InitVertexBuffer(pD3DDevice);
	if (error != 0)
		return error;

	error = InitIndexBuffer(pD3DDevice);
	if (error != 0)
		return error;

	XMMATRIX identityMatrix = XMMatrixIdentity();
	XMFLOAT4X4 identityFloat4x4 = {};
	XMStoreFloat4x4(&identityFloat4x4, identityMatrix);
	transformMatrix = *reinterpret_cast<D3DMATRIX*>(&identityFloat4x4);

	return 0;
}

void Mesh::Update()
{
	XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(0.0f, 0.0f, XM_PIDIV4);
	XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(&transformMatrix), rotationMatrix);
}

void Mesh::Render(IDirect3DDevice9* pD3DDevice)
{
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

	vertices[0] = Vertex(-0.5f,  0.5f, 0.0f, 255,   0,   0);
	vertices[1] = Vertex( 0.5f,  0.5f, 0.0f,   0, 255,   0);
	vertices[2] = Vertex( 0.5f, -0.5f, 0.0f, 255,   0, 255);
	vertices[3] = Vertex(-0.5f, -0.5f, 0.0f,   0,   0, 255);

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
