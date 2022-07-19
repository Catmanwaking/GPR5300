#pragma once
#include <d3d9.h>

#define FVF D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1

struct Vertex
{
	FLOAT x;
	FLOAT y;
	FLOAT z;

	D3DCOLOR color;

	FLOAT u;
	FLOAT v;

	Vertex();
	Vertex(FLOAT x, FLOAT y, FLOAT z);
	Vertex(FLOAT x, FLOAT y, FLOAT z, D3DCOLOR color);
	Vertex(FLOAT x, FLOAT y, FLOAT z, BYTE r, BYTE g, BYTE b);
	Vertex(FLOAT x, FLOAT y, FLOAT z, FLOAT u, FLOAT v);
};