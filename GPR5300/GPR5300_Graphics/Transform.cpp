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

Vector3 Transform::GetPosition()
{
	return Vector3(position.x, position.y, position.z);
}

Vector3 Transform::GetRotation()
{
	return Vector3(rotation.x, rotation.y, rotation.z);
}

Vector3 Transform::GetScale()
{
	return Vector3(scale.x, scale.y, scale.z);
}

Vector3 Transform::Forward()
{
	return Vector3
	(
		cosf(rotation.z) * sinf(rotation.y),
		-sinf(rotation.z),
		cosf(rotation.z) * cosf(rotation.y)
	);
}

Vector3 Transform::Back()
{
	return Vector3
	(
		-cosf(rotation.z) * sinf(rotation.y),
		sinf(rotation.z),
		-cosf(rotation.z) * cosf(rotation.y)
	);
}

Vector3 Transform::Right()
{
	return Vector3
	(
		cosf(rotation.y),
		0.0f,
		-sinf(rotation.y)
	);
}

Vector3 Transform::Left()
{
	return Vector3
	(
		-cosf(rotation.y),
		0.0f,
		sinf(rotation.y)
	);
}

Vector3 Transform::Up()
{
	return Vector3
	(
		sinf(rotation.z) * sinf(rotation.y),
		cosf(rotation.z),
		sinf(rotation.z) * cosf(rotation.y)
	);
}

Vector3 Transform::Down()
{
	return Vector3
	(
		-sinf(rotation.z) * sinf(rotation.y),
		-cosf(rotation.z),
		-sinf(rotation.z) * cosf(rotation.y)
	);
}

Transform Transform::operator*(FLOAT right)
{
	Transform left;
	left.position = this->position * right;
	left.rotation = this->rotation * right;
	left.scale = this->scale * right;
	return left;
}

void Transform::operator*=(FLOAT right)
{
	this->position *= right;
	this->rotation *= right;
	this->scale *= right;
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
