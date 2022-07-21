#include "Vertex.h"
#include <DirectXMath.h>

using namespace DirectX;

Vertex::Vertex()
{ 
	this->x = 0.0f, 
	this->y = 0.0f, 
	this->z = 0.0f, 
	this->nx = 0.0f,
	this->ny = 0.0f,
	this->nz = 0.0f,
	this->color = 0xffffffff, 
	this->u = 0.0f, 
	this->v = 0.0f; 
}

Vertex::Vertex(FLOAT x, FLOAT y, FLOAT z) 
{ 
	this->x = x, 
	this->y = y, 
	this->z = z,
	this->nx = 0.0f,
	this->ny = 0.0f,
	this->nz = 0.0f,
	this->color = 0xffffffff, 
	this->u = 0.0f, 
	this->v = 0.0f; 
}

Vertex::Vertex(FLOAT x, FLOAT y, FLOAT z, D3DCOLOR color)
{
	this->x = x,
	this->y = y,
	this->z = z,
	this->nx = 0.0f,
	this->ny = 0.0f,
	this->nz = 0.0f,
	this->color = color,
	this->u = 0.0f,
	this->v = 0.0f;
}

Vertex::Vertex(FLOAT x, FLOAT y, FLOAT z, BYTE r, BYTE g, BYTE b)
{
	this->x = x,
	this->y = y,
	this->z = z,
	this->nx = 0.0f,
	this->ny = 0.0f,
	this->nz = 0.0f,
	this->color = D3DCOLOR_XRGB(r,g,b),
	this->u = 0.0f,
	this->v = 0.0f;
}

Vertex::Vertex(FLOAT x, FLOAT y, FLOAT z, FLOAT u, FLOAT v)
{
	this->x = x,
	this->y = y,
	this->z = z,
	this->nx = 0.0f,
	this->ny = 0.0f,
	this->nz = 0.0f,
	this->color = 0xffffffff,
	this->u = u,
	this->v = v;
}

Vertex::Vertex(FLOAT x, FLOAT y, FLOAT z, FLOAT nx, FLOAT ny, FLOAT nz, FLOAT u, FLOAT v)
{
	this->x = x,
	this->y = y,
	this->z = z,
	this->nx = nx,
	this->ny = ny,
	this->nz = nz,
	this->color = 0xffffffff,
	this->u = u,
	this->v = v;
}

Vertex::Vertex(XMFLOAT3 position, XMFLOAT3 normal, XMFLOAT2 texCoord)
{
	this->x = position.x,
	this->y = position.y,
	this->z = position.z,
	this->nx = normal.x,
	this->ny = normal.y,
	this->nz = normal.z,
	this->color = 0xffffffff,
	this->u = texCoord.x,
	this->v = texCoord.y;
}
