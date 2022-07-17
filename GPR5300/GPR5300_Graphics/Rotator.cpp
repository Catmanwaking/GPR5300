#include "Rotator.h"

INT Rotator::Init(Vector3 rotation, Time* pTime)
{
	this->rotation = rotation;
	this->pTime = pTime;
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
