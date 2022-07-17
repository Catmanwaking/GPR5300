#include "Mover.h"

INT Mover::Init(Transform movement)
{
	this->movement = movement;
	return 0;
}

void Mover::Update()
{
	*pTransform += movement;
}

void Mover::DeInit()
{
}
