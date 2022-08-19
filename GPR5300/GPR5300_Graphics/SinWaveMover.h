#pragma once
#include <d3d11.h>
#include "Component.h"
#include "IUpdateable.h"
#include "Transform.h"
#include "Time.h"
#include "Space.h"

class SinWaveMover : public Component, public IUpdateable
{
public:
	//Initializes the SinWaveMover component.
	INT Init(Vector3 movement, Vector3 anchor, FLOAT speed);
	//Updates the position of the GameObject.
	virtual void Update();
	virtual void DeInit();

	//Sets the movement space.
	void SetSpace(Space relativeTo);

private:
	Vector3 movement = {};
	Time* pTime = nullptr;
	Space relativeTo = Space::Global;

	FLOAT speed = 1.0f;
	FLOAT time = 0.0f;
	Vector3 position = {};
};

