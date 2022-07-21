#pragma once
#include <DirectXMath.h>

using namespace DirectX;

struct Vertex
{
	XMFLOAT3 pos;
	XMFLOAT3 normal;
	XMFLOAT2 uv;
	XMFLOAT4 color;

	Vertex() : pos(0.0f,0.0f,0.0f), normal(0.0f, 0.0f, 0.0f), uv(0.0f, 0.0f), color(1.0f, 1.0f, 1.0f, 1.0f) {}
	Vertex(FLOAT x, FLOAT y, FLOAT z) : pos(x, y, z), normal(0.0f, 0.0f, 0.0f), uv(0.0f, 0.0f), color(1.0f, 1.0f, 1.0f, 1.0f) {}
	Vertex(FLOAT x, FLOAT y, FLOAT z, FLOAT r, FLOAT g, FLOAT b) : pos(x, y, z), normal(0.0f, 0.0f, 0.0f), uv(0.0f, 0.0f), color(r, g, b, 1.0f) {}
	Vertex(FLOAT x, FLOAT y, FLOAT z, FLOAT u, FLOAT v) : pos(x, y, z), normal(0.0f, 0.0f, 0.0f), uv(u, v), color(1.0f, 1.0f, 1.0f, 1.0f) {}
	Vertex(FLOAT x, FLOAT y, FLOAT z, FLOAT nx, FLOAT ny, FLOAT nz, FLOAT u, FLOAT v) : pos(x, y, z), normal(nx, ny, nz), uv(u, v), color(1.0f, 1.0f, 1.0f, 1.0f) {}
};