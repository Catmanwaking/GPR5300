#pragma once
#include <d3d11.h>
#include "Vector3.h"
#include "Component.h"
#include "IUpdateable.h"
#include "Time.h"
#include "Space.h"

class Rotator : public Component, public IUpdateable
{
public:
	//Initializes the Rotator component.
	INT Init(Vector3 rotation);
	//Updates the GameObjects rotation.
	virtual void Update();
	virtual void DeInit();

	//Sets the rotation space.
	void SetSpace(Space relativeTo);

private:
	Vector3 rotation = {};
	Time* pTime = nullptr;
	Space relativeTo = Space::Global;
};

