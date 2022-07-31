#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "Vector3.h"

using namespace DirectX;

class Quaternion
{
public:
	FLOAT w, x, y, z;

	Quaternion() { w = 1.0f, x = 0.0f, y = 0.0f, z = 0.0f; }
	Quaternion(FLOAT w, FLOAT x, FLOAT y, FLOAT z) { this->w = w, this->x = x, this->y = y, this->z = z; }
	Quaternion(Vector3 euler);

	FLOAT Magnitude() const;
	Quaternion Conjugation() const;
	void Conjugate();
	Quaternion Normalized() const;
	void Normalize();

	void RotateAround(Vector3 axis, FLOAT angle);

	XMVECTOR ToXMVector() { return { x,y,z,w }; };

	Quaternion operator *(FLOAT scalar);
	void operator *=(FLOAT scalar);
	Quaternion operator *(const Quaternion q);
	void operator *=(const Quaternion q);

	Vector3 operator *(const Vector3 v);
};

