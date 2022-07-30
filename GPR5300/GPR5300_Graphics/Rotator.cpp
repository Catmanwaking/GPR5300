#include "Rotator.h"

INT Rotator::Init(Vector3 rotation)
{
	this->rotation = rotation;
	this->pTime = Time::GetInstance();
    return 0;
}

void Rotator::Update()
{
	FLOAT deltaTime = pTime->GetDeltaTime();
	if (relativeTo == Space::Global)
	{
		pTransform->rotation.RotateAround(Vector3::Forward(), rotation.z * deltaTime);
		pTransform->rotation.RotateAround(Vector3::Right(), rotation.x * deltaTime);
		pTransform->rotation.RotateAround(Vector3::Up(), rotation.y * deltaTime);
	}
	else
	{
		pTransform->rotation.RotateAround(pTransform->Forward(), rotation.z * deltaTime);
		pTransform->rotation.RotateAround(pTransform->Right(), rotation.x * deltaTime);
		pTransform->rotation.RotateAround(pTransform->Up(), rotation.y * deltaTime);
	}
}

void Rotator::DeInit()
{
}

void Rotator::SetSpace(Space relativeTo)
{
    this->relativeTo = relativeTo;
}
