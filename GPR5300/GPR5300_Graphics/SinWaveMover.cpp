#include "SinWaveMover.h"

INT SinWaveMover::Init(Vector3 movement, Vector3 anchor, FLOAT speed)
{
	this->movement = movement;
	this->pTime = Time::GetInstance();
	this->position = anchor;
	this->speed = speed;
	return 0;
}

void SinWaveMover::Update()
{
	time += pTime->GetDeltaTime();
	FLOAT sin = sinf(time * speed);
	
	if (relativeTo == Space::Global)
		pTransform->position = position + movement * sin;
	else
	{
		pTransform->position = position + 
			pTransform->Right() * (movement.x * sin) +
			pTransform->Up() * (movement.y * sin) +
			pTransform->Forward() * (movement.z * sin);
	}
}

void SinWaveMover::DeInit()
{
}

void SinWaveMover::SetSpace(Space relativeTo)
{
	this->relativeTo = relativeTo;
}
