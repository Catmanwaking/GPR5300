#include "Mover.h"

INT Mover::Init(Vector3 movement)
{
	this->movement = movement;
	this->pTime = Time::GetInstance();
	return 0;
}

void Mover::Update()
{
	FLOAT deltaTime = pTime->GetDeltaTime();
	if(relativeTo == Space::Global)
		pTransform->position += movement * deltaTime;
	else
	{
		pTransform->position += pTransform->Right() * (movement.x * deltaTime);
		pTransform->position += pTransform->Up() * (movement.y * deltaTime);
		pTransform->position += pTransform->Forward() * (movement.z * deltaTime);
	}
}

void Mover::DeInit()
{
}

void Mover::SetSpace(Space relativeTo)
{
	this->relativeTo = relativeTo;
}
