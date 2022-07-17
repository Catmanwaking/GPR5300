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
	Vector3 GetPosition();
	Vector3 GetRotation();
	Vector3 GetScale();
	Vector3 Forward();
	Vector3 Back();
	Vector3 Right();
	Vector3 Left();
	Vector3 Up();
	Vector3 Down();

	Transform operator *(FLOAT right);
	void operator *=(FLOAT right);

	Transform operator +(Transform right);
	void operator +=(Transform right);
};

