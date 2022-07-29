#pragma once
#include <d3d9.h>
#include "Component.h"
#include "IUpdateable.h"
#include "Time.h"

class PlayerController : public Component, public IUpdateable
{
public:
	INT Init(UINT width, UINT height);
	virtual void Update();
	virtual void DeInit();

private:
	const FLOAT sensitivity = 2.5f;
	const FLOAT moveSpeed = 2.0f;
	const FLOAT speedModifier = 3.0f;
	Time* pTime = nullptr;
	POINT pos = {};
	POINT screenCenter = {};

	void Move(FLOAT time);
	void Rotate(FLOAT time);
};

