#pragma once
#include "Vector3.h"

class Transform
{
public:
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

	Transform() 
	{
		position = Vector3(0.0f, 0.0f, 0.0f),
		rotation = Vector3(0.0f, 0.0f, 0.0f),
		scale = Vector3(1.0f, 1.0f, 1.0f);
	};
	Transform(FLOAT posX, FLOAT posY, FLOAT posZ, FLOAT rotX, FLOAT rotY, FLOAT rotZ, FLOAT scaX, FLOAT scaY, FLOAT scaZ)
	{ 
		position = Vector3(posX, posY, posZ),
		rotation = Vector3(rotX, rotY, rotZ),
		scale = Vector3(scaX, scaY, scaZ);
	}
	Transform(Vector3 pos, Vector3 rot, Vector3 sca) 
	{
		position = pos,
		rotation = rot,
		scale = sca;
	};

};

