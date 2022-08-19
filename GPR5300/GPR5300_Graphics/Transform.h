#pragma once
#include "Vector3.h"
#include "Quaternion.h"

class Transform
{
public:
	Vector3 position = {};
	Quaternion rotation = {};
	Vector3 scale = {};

	Transform();
	Transform(FLOAT posX, FLOAT posY, FLOAT posZ, FLOAT rotX, FLOAT rotY, FLOAT rotZ, FLOAT scaX, FLOAT scaY, FLOAT scaZ);
	Transform(Vector3 pos, Quaternion rot, Vector3 sca);

	//Calculates the transformation (world) matrix of the object.
	XMMATRIX GetTransformationMatrix();
	//Returns the position of the object.
	Vector3 GetPosition();
	//Returns the rotation of the object.
	Quaternion GetRotation();
	//Returns the Scale of the object.
	Vector3 GetScale();
	//Calculates the local forward Vector of the object.
	Vector3 Forward();
	//Calculates the local backward Vector of the object.
	Vector3 Back();
	//Calculates the local right Vector of the object.
	Vector3 Right();
	//Calculates the local left Vector of the object.
	Vector3 Left();
	//Calculates the local up Vector of the object.
	Vector3 Up();
	//Calculates the local down Vector of the object.
	Vector3 Down();
};

