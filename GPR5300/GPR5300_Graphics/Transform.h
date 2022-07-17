#pragma once
#include "Vector3.h"

class Transform
{
public:
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

	Transform();
	Transform(FLOAT posX, FLOAT posY, FLOAT posZ, FLOAT rotX, FLOAT rotY, FLOAT rotZ, FLOAT scaX, FLOAT scaY, FLOAT scaZ);
	Transform(Vector3 pos, Vector3 rot, Vector3 sca);

	XMMATRIX GetTransformationMatrix();
	XMVECTOR GetPosition();
	XMVECTOR GetRotation();
	XMVECTOR GetScale();
	XMVECTOR Forward();
	XMVECTOR Back();
	XMVECTOR Right();
	XMVECTOR Left();
	XMVECTOR Up();
	XMVECTOR Down();

	Transform operator +(Transform right);
	void operator +=(Transform right);
};

