#include "Vertex.h"

Vertex::Vertex()
{ 
	this->x = 0.0f, 
	this->y = 0.0f, 
	this->z = 0.0f, 
	this->color = 0xffffffff, 
	this->u = 0.0f, 
	this->v = 0.0f; 
}

Vertex::Vertex(FLOAT x, FLOAT y, FLOAT z) 
{ 
	this->x = x, 
	this->y = y, 
	this->z = z, 
	this->color = 0xffffffff, 
	this->u = 0.0f, 
	this->v = 0.0f; 
}

Vertex::Vertex(FLOAT x, FLOAT y, FLOAT z, D3DCOLOR color)
{
	this->x = x,
	this->y = y,
	this->z = z,
	this->color = color,
	this->u = 0.0f,
	this->v = 0.0f;
}

Vertex::Vertex(FLOAT x, FLOAT y, FLOAT z, BYTE r, BYTE g, BYTE b)
{
	this->x = x,
	this->y = y,
	this->z = z,
	this->color = D3DCOLOR_XRGB(r,g,b),
	this->u = 0.0f,
	this->v = 0.0f;
}

Vertex::Vertex(FLOAT x, FLOAT y, FLOAT z, FLOAT u, FLOAT v)
{
	this->x = x,
	this->y = y,
	this->z = z,
	this->color = 0xffffffff,
	this->u = u,
	this->v = v;
}
