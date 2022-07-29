#pragma once
#include <d3d9.h>
#include <DirectXMath.h>

using namespace DirectX;

class Vector2
{
public:
	FLOAT x;
	FLOAT y;

	Vector2() { x = 0.0f, y = 0.0f; }
	Vector2(FLOAT x, FLOAT y) { this->x = x, this->y = y; }
	XMFLOAT2 ToXMFloat() { return XMFLOAT2(x, y); }
	XMVECTOR ToXMVector() { return XMVectorSet(x, y, 0.0f, 0.0f); }

	Vector2 operator *(FLOAT right);
	void operator *=(FLOAT right);
	Vector2 operator +(Vector2 right);
	void operator +=(Vector2 right);
	Vector2 operator -(Vector2 right);
	void operator -=(Vector2 right);
	FLOAT operator *(Vector2 right);
};
