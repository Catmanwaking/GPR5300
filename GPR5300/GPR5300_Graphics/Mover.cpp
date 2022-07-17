#include "Mover.h"

INT Mover::Init(Transform movement, Time* pTime)
{
	this->movement = movement;
	this->pTime = pTime;
	return 0;
}

void Mover::Update()
{
	FLOAT deltaTime = pTime->GetDeltaTime();
	if(relativeTo == Space::Global)
		*pTransform += movement * deltaTime;
	else
	{
		pTransform->position += pTransform->Right() * (movement.position.x * deltaTime);
		pTransform->position += pTransform->Up() * (movement.position.y * deltaTime);
		pTransform->position += pTransform->Forward() * (movement.position.z * deltaTime);
		pTransform->rotation += movement.rotation * deltaTime;
		pTransform->scale += movement.scale * deltaTime;
	}
}

void Mover::DeInit()
{
}
