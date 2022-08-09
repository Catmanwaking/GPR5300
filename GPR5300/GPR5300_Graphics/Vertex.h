#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

struct Vertex
{
	XMFLOAT3 pos = {};
	XMFLOAT3 normal = {};
	XMFLOAT2 uv = {};
	XMFLOAT3 tangent = {};
	XMFLOAT3 binormal = {};

	Vertex();
	Vertex(FLOAT x, FLOAT y, FLOAT z);
	Vertex(FLOAT x, FLOAT y, FLOAT z, FLOAT r, FLOAT g, FLOAT b);
	Vertex(FLOAT x, FLOAT y, FLOAT z, FLOAT u, FLOAT v);
	Vertex(FLOAT x, FLOAT y, FLOAT z, FLOAT nx, FLOAT ny, FLOAT nz, FLOAT u, FLOAT v);
	Vertex(XMFLOAT3 position, XMFLOAT3 normal, XMFLOAT2 uv);
};