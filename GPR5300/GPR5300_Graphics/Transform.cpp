#include "Transform.h"

Transform::Transform()
{
	position = Vector3(0.0f, 0.0f, 0.0f);
	rotation = Vector3(0.0f, 0.0f, 0.0f);
	scale = Vector3(1.0f, 1.0f, 1.0f);
}

Transform::Transform(FLOAT posX, FLOAT posY, FLOAT posZ, FLOAT rotX, FLOAT rotY, FLOAT rotZ, FLOAT scaX, FLOAT scaY, FLOAT scaZ)
{
	position = Vector3(posX, posY, posZ);
	rotation = Vector3(rotX, rotY, rotZ);
	scale = Vector3(scaX, scaY, scaZ);
}

Transform::Transform(Vector3 pos, Vector3 rot, Vector3 sca)
{
	position = pos;
	rotation = rot;
	scale = sca;
}

XMMATRIX Transform::GetTransformationMatrix()
{
	return 
		XMMatrixScaling(scale.x, scale.y, scale.z) *
		XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z) *
		XMMatrixTranslation(position.x, position.y, position.z);
}

XMVECTOR Transform::GetPosition()
{
	return XMVectorSet(position.x, position.y, position.z, 0.0f);
}

XMVECTOR Transform::GetRotation()
{
	return XMVectorSet(rotation.x, rotation.y, rotation.z, 0.0f);
}

XMVECTOR Transform::GetScale()
{
	return XMVectorSet(scale.x, scale.y, scale.z, 0.0f);
}

XMVECTOR Transform::Forward()
{
	return XMVectorSet
	(
		cos(rotation.z) * sin(rotation.y),
		-sin(rotation.z),
		cos(rotation.z) * cos(rotation.y),
		0.0f
	);
}

XMVECTOR Transform::Back()
{
	return XMVectorSet
	(
		-cos(rotation.z) * sin(rotation.y),
		sin(rotation.z),
		-cos(rotation.z) * cos(rotation.y),
		0.0f
	);
}

XMVECTOR Transform::Right()
{
	return XMVectorSet
	(
		cos(rotation.y),
		0.0f,
		-sin(rotation.y),
		0.0f
	);
}

XMVECTOR Transform::Left()
{
	return XMVectorSet
	(
		-cos(rotation.y),
		0.0f,
		sin(rotation.y),
		0.0f
	);
}

XMVECTOR Transform::Up()
{
	return XMVectorSet
	(
		sin(rotation.z) * sin(rotation.y),
		cos(rotation.z),
		sin(rotation.z) * cos(rotation.y),
		0.0f
	);
}

XMVECTOR Transform::Down()
{
	return XMVectorSet
	(
		-sin(rotation.z) * sin(rotation.y),
		-cos(rotation.z),
		-sin(rotation.z) * cos(rotation.y),
		0.0f
	);
}

Transform Transform::operator+(Transform right)
{
	Transform left;
	left.position = this->position + right.position;
	left.rotation = this->rotation + right.rotation;
	left.scale = this->scale + right.scale;
	return left;
}

void Transform::operator+=(Transform right)
{
	this->position += right.position;
	this->rotation += right.rotation;
	this->scale += right.scale;
}
