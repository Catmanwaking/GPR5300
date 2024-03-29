#include "Vertex.h"
#include <DirectXMath.h>

using namespace DirectX;

Vertex::Vertex()
{ 
	pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	uv = XMFLOAT2(0.0f, 0.0f);
	normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
}

Vertex::Vertex(FLOAT x, FLOAT y, FLOAT z) 
{ 
	pos = XMFLOAT3(x, y, z);
	uv = XMFLOAT2(0.0f, 0.0f);
	normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
}

Vertex::Vertex(FLOAT x, FLOAT y, FLOAT z, FLOAT r, FLOAT g, FLOAT b)
{
	pos = XMFLOAT3(x, y, z);
	uv = XMFLOAT2(0.0f, 0.0f);
	normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
}

Vertex::Vertex(FLOAT x, FLOAT y, FLOAT z, FLOAT u, FLOAT v)
{
	pos = XMFLOAT3(x, y, z);
	uv = XMFLOAT2(u, v);
	normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
}

Vertex::Vertex(FLOAT x, FLOAT y, FLOAT z, FLOAT nx, FLOAT ny, FLOAT nz, FLOAT u, FLOAT v)
{
	pos = XMFLOAT3(x, y, z);
	uv = XMFLOAT2(u, v);
	normal = XMFLOAT3(nx, ny, nz);
}

Vertex::Vertex(XMFLOAT3 position, XMFLOAT3 normal, XMFLOAT2 texCoord)
{
	this->pos = position;
	this->uv = texCoord;
	this->normal = normal;
}
