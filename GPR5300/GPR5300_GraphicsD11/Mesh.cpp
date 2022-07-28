#include "Mesh.h"
#include "Vertex.h"
#include "Utils.h"

INT Mesh::Init(ID3D11Device* pD3DDevice)
{
	INT error = 0;

	error = InitVertexBuffer(pD3DDevice);
	if (error != 0)
		return error;

	error = InitIndexBuffer(pD3DDevice);
	if (error != 0)
		return error;

	XMStoreFloat4x4(&transformMatrix, XMMatrixIdentity());

	return 0;
}

void Mesh::Update()
{
	static float rot = 0.0f;
	if (GetAsyncKeyState('W') & 0x8000)
		rot -= 0.001f;
	if (GetAsyncKeyState('S') & 0x8000)
		rot += 0.001f;

	XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(0.0f, rot, 0.0f);
	XMMATRIX transform = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	XMMATRIX scaleMatrix = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	XMStoreFloat4x4(&transformMatrix, scaleMatrix * rotationMatrix * transform);
}

void Mesh::Render(ID3D11DeviceContext* pD3DDeviceContext)
{
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
	vertexCount = 4;
	vertexStride = sizeof(Vertex);

	Vertex vertices[] = 
	{
		Vertex(-0.5f,  0.5f,  0.0f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f),
		Vertex( 0.5f,  0.5f,  0.0f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f),
		Vertex( 0.5f, -0.5f,  0.0f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f),
		Vertex(-0.5f, -0.5f,  0.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f)
	};

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.ByteWidth = vertexCount * vertexStride;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;

	D3D11_SUBRESOURCE_DATA subResourceData = {};
	subResourceData.pSysMem = vertices;

	HRESULT hr = pD3DDevice->CreateBuffer(&bufferDesc, &subResourceData, &pVertexBuffer);
	if (FAILED(hr)) return 30;

	return 0;
}

INT Mesh::InitIndexBuffer(ID3D11Device* pD3DDevice)
{
	indexCount = 6;

	USHORT indices[]
	{
		0, 1, 2,
		0, 2, 3
	};

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.ByteWidth = indexCount * sizeof(USHORT);
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;

	D3D11_SUBRESOURCE_DATA subResourceData = {};
	subResourceData.pSysMem = indices;

	HRESULT hr = pD3DDevice->CreateBuffer(&bufferDesc, &subResourceData, &pIndexBuffer);
	if (FAILED(hr)) return 32;

	return 0;
}
