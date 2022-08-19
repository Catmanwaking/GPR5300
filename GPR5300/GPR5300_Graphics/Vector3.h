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
	Vector3(XMFLOAT3 input) { x = input.x, y = input.y, z = input.z; }

	//Calculates the length of the Vector.
	FLOAT Length();
	//Calculates the squared length of the Vector.
	FLOAT LengthSqr();
	//Normalizes the Vector.
	void Normalize();

	//Converts the Vector to XMFLOAT3
	XMFLOAT3 ToXMFloat3() { return XMFLOAT3(x, y, z); }
	//Converts the Vector to XMVECTOR
	XMVECTOR ToXMVector() { return XMVectorSet(x, y, z, 0.0f); }

	//Returns a Vector pointing up.
	static Vector3 Up()			{ return Vector3( 0.0f,  1.0f,  0.0f); }
	//Returns a Vector pointing down.
	static Vector3 Down()		{ return Vector3( 0.0f, -1.0f,  0.0f); }
	//Returns a Vector pointing right.
	static Vector3 Right()		{ return Vector3( 1.0f,  0.0f,  0.0f); }
	//Returns a Vector pointing left.
	static Vector3 Left()		{ return Vector3(-1.0f,  0.0f,  0.0f); }
	//Returns a Vector pointing forward.
	static Vector3 Forward()	{ return Vector3( 0.0f,  0.0f,  1.0f); }
	//Returns a Vector pointing back.
	static Vector3 Back()		{ return Vector3( 0.0f,  0.0f, -1.0f); }

	Vector3 operator *(FLOAT scalar);
	void operator *=(FLOAT scalar);
	Vector3 operator +(Vector3 v);
	void operator +=(Vector3 v);
	Vector3 operator -(Vector3 v);
	void operator -=(Vector3 v);

	FLOAT operator *(Vector3 v);

	//Calculates the crossproduct of two Vectors.
	static Vector3 Cross(Vector3 v1, Vector3 v2);
};
