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

	//Calculates the magnitude of the Quaternion.
	FLOAT Magnitude() const;

	//Returns the conjugate of the Quaternion.
	Quaternion Conjugation() const;
	//Inverts the Quaternion
	void Conjugate();
	//Returns the normalized Quaternion.
	Quaternion Normalized() const;
	//Normalizes the Quaternion.
	void Normalize();

	//Rotates the Quaternion around the specified angle.
	void RotateAround(Vector3 axis, FLOAT angle);

	//Converts the Quaternion to XMVECTOR in the order x,y,z,w.
	XMVECTOR ToXMVector() { return { x,y,z,w }; };

	Quaternion operator *(FLOAT scalar);
	void operator *=(FLOAT scalar);
	Quaternion operator *(const Quaternion q);
	void operator *=(const Quaternion q);

	Vector3 operator *(const Vector3 v);

	//Calculates a Quaternion that rotates an object toward the specified Vector.
	static Quaternion LookTo(Vector3 lookDir);
	//Calculates a Quaternion that represents a rotation from the first vector to the second.
	static Quaternion FromToRotation(Vector3 v1, Vector3 v2);
};

