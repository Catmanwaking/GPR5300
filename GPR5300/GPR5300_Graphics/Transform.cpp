#include "Transform.h"

Transform::Transform()
{
	position = Vector3(0.0f, 0.0f, 0.0f);
	rotation = Quaternion(1.0f, 0.0f, 0.0f,0.0f);
	scale = Vector3(1.0f, 1.0f, 1.0f);
}

Transform::Transform(FLOAT posX, FLOAT posY, FLOAT posZ, FLOAT rotX, FLOAT rotY, FLOAT rotZ, FLOAT scaX, FLOAT scaY, FLOAT scaZ)
{
	position = Vector3(posX, posY, posZ);
	rotation = Quaternion(Vector3(rotX, rotY, rotZ));
	scale = Vector3(scaX, scaY, scaZ);
}

Transform::Transform(Vector3 pos, Quaternion rot, Vector3 sca)
{
	position = pos;
	rotation = rot;
	scale = sca;
}

XMMATRIX Transform::GetTransformationMatrix()
{
	return 
		XMMatrixScaling(scale.x, scale.y, scale.z) *
		XMMatrixRotationQuaternion(rotation.ToXMVector()) * 
		XMMatrixTranslation(position.x, position.y, position.z);
}

Vector3 Transform::GetPosition()
{
	return Vector3(position.x, position.y, position.z);
}

Quaternion Transform::GetRotation()
{
	return Quaternion(rotation.w, rotation.x, rotation.y, rotation.z);
}

Vector3 Transform::GetScale()
{
	return Vector3(scale.x, scale.y, scale.z);
}

Vector3 Transform::Forward()
{
	return rotation * Vector3::Forward();
}

Vector3 Transform::Back()
{
	return rotation * Vector3::Back();
}

Vector3 Transform::Right()
{
	return rotation * Vector3::Right();
}

Vector3 Transform::Left()
{
	return rotation * Vector3::Left();
}

Vector3 Transform::Up()
{
	return rotation * Vector3::Up();
}

Vector3 Transform::Down()
{
	return rotation * Vector3::Down();
}
