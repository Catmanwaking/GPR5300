#pragma once
#include <d3d9.h>

#define FVF D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1

struct Vertex
{
	FLOAT x;
	FLOAT y;
	FLOAT z;

	FLOAT nx;
	FLOAT ny;
	FLOAT nz;

	D3DCOLOR color;

	FLOAT u;
	FLOAT v;

	Vertex() : x(0.0f), y(0.0f), z(0.0f), nx(0.0f), ny(0.0f), nz(0.0f), color(0xffffffff), u(0.0f), v(0.0f) {}
	Vertex(FLOAT x, FLOAT y, FLOAT z) : x(x), y(y), z(z), nx(0.0f), ny(0.0f), nz(0.0f), color(0xffffffff), u(0.0f), v(0.0f) {}
	Vertex(FLOAT x, FLOAT y, FLOAT z, D3DCOLOR color) : x(x), y(y), z(z), nx(0.0f), ny(0.0f), nz(0.0f), color(color), u(0.0f), v(0.0f) {}
	Vertex(FLOAT x, FLOAT y, FLOAT z, BYTE r, BYTE g, BYTE b) : x(x), y(y), z(z), nx(0.0f), ny(0.0f), nz(0.0f), color(D3DCOLOR_XRGB(r,g,b)), u(0.0f), v(0.0f) {}
	Vertex(FLOAT x, FLOAT y, FLOAT z, FLOAT u, FLOAT v) : x(x), y(y), z(z), nx(0.0f), ny(0.0f), nz(0.0f), color(0xffffffff), u(u), v(v) {}
	Vertex(FLOAT x, FLOAT y, FLOAT z, FLOAT nx, FLOAT ny, FLOAT nz, FLOAT u, FLOAT v) : x(x), y(y), z(z), nx(nx), ny(ny), nz(nz), color(0xffffffff), u(u), v(v) {}
};