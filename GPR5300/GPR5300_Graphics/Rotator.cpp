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
		pTransform->rotation += rotation * deltaTime;
	else
		pTransform->rotation += rotation * deltaTime; //TODO
}

void Rotator::DeInit()
{
}

void Rotator::SetSpace(Space relativeTo)
{
    this->relativeTo = relativeTo;
}
