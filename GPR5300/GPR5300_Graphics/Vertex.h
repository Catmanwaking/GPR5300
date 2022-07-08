#pragma once
#include <d3d9.h>

#define FVF D3DFVF_XYZ | D3DFVF_DIFFUSE

struct Vertex
{
	FLOAT x;
	FLOAT y;
	FLOAT z;

	D3DCOLOR color;

	Vertex() : x(0.0f), y(0.0f), z(0.0f), color(0xffffffff) {}
	Vertex(FLOAT x, FLOAT y, FLOAT z) : x(x), y(y), z(z), color(0xffffffff) {}
	Vertex(FLOAT x, FLOAT y, FLOAT z, D3DCOLOR color) : x(x), y(y), z(z), color(color) {}
	Vertex(FLOAT x, FLOAT y, FLOAT z, BYTE r, BYTE g, BYTE b) : x(x), y(y), z(z), color(D3DCOLOR_XRGB(r,g,b)) {}
};