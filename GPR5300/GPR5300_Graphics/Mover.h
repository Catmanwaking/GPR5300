#pragma once
#include <d3d11.h>
#include "Component.h"
#include "IUpdateable.h"
#include "Transform.h"
#include "Time.h"
#include "Space.h"

class Mover : public Component, public IUpdateable
{
public:
	//Initializes the Mover Component.
	INT Init(Vector3 movement);
	//Updates the position of the GameObject.
	virtual void Update();
	virtual void DeInit();

	//Sets the movement space.
	void SetSpace(Space relativeTo);

private:
	Vector3 movement = {};
	Time* pTime = nullptr;
	Space relativeTo = Space::Global;
};

