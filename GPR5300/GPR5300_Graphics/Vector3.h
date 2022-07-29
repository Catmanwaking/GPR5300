#pragma once
#include <d3d9.h>
#include <DirectXMath.h>
#include "Math.h"

using namespace DirectX;

class Vector3
{
public:
	FLOAT x;
	FLOAT y;
	FLOAT z;

	Vector3() { x = 0.0f, y = 0.0f, z = 0.0f; }
	Vector3(FLOAT x, FLOAT y, FLOAT z) { this->x = x, this->y = y, this->z = z; }

	FLOAT Length();
	FLOAT LengthSqr();
	void Normalize();

	XMFLOAT3 ToXMFloat() { return XMFLOAT3(x, y, z); }
	XMVECTOR ToXMVector() { return XMVectorSet(x, y, z, 0.0f); }

	Vector3 operator *(FLOAT right);
	void operator *=(FLOAT right);
	Vector3 operator +(Vector3 right);
	void operator +=(Vector3 right);
	Vector3 operator -(Vector3 right);
	void operator -=(Vector3 right);
	FLOAT operator *(Vector3 right);
};
