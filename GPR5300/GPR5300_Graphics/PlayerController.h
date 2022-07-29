#pragma once
#include <d3d9.h>
#include "Component.h"
#include "IUpdateable.h"
#include "MouseInputManager.h"
#include "Time.h"

class PlayerController : public Component, public IUpdateable
{
public:
	INT Init();
	virtual void Update();
	virtual void DeInit();

private:
	const FLOAT sensitivity = 2.5f;
	MouseInputManager* pMouseInputManager = nullptr;
	Time* pTime = nullptr;
	POINT pos = {};
	POINT lastPos = {};
};

