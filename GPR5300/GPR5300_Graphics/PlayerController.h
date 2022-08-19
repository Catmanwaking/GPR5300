#pragma once
#include <d3d11.h>
#include "Component.h"
#include "IUpdateable.h"
#include "Time.h"
#include "Vector3.h"

class PlayerController : public Component, public IUpdateable
{
public:
	//Initializes the PlayerController component
	INT Init();
	//Updates the GameObjects position and rotation based on mouse and keyboard inputs.
	virtual void Update();
	virtual void DeInit();

private:
	const FLOAT sensitivity = 250.0f;
	const FLOAT moveSpeed = 5.0f;
	const FLOAT speedModifier = 3.0f;
	Time* pTime = nullptr;
	POINT pos = {};
	POINT screenCenter = {};
	Vector3 camRotation = {};

	//Moves the GameObject based on keyboard inputs.
	void Move(FLOAT time);
	//Rotates the GameObject based on mouse inputs.
	void Rotate(FLOAT time);
};

