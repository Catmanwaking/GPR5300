#pragma once
#include <d3d11.h>
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

	XMFLOAT3 ToXMFloat3() { return XMFLOAT3(x, y, z); }
	XMVECTOR ToXMVector() { return XMVectorSet(x, y, z, 0.0f); }

	static Vector3 Up()			{ return Vector3( 0.0f,  1.0f,  0.0f); }
	static Vector3 Down()		{ return Vector3( 0.0f, -1.0f,  0.0f); }
	static Vector3 Right()		{ return Vector3( 1.0f,  0.0f,  0.0f); }
	static Vector3 Left()		{ return Vector3(-1.0f,  0.0f,  0.0f); }
	static Vector3 Forward()	{ return Vector3( 0.0f,  0.0f,  1.0f); }
	static Vector3 Back()		{ return Vector3( 0.0f,  0.0f, -1.0f); }

	Vector3 operator *(FLOAT scalar);
	void operator *=(FLOAT scalar);
	Vector3 operator +(Vector3 v);
	void operator +=(Vector3 v);
	Vector3 operator -(Vector3 v);
	void operator -=(Vector3 v);

	FLOAT operator *(Vector3 v);
};
