#pragma once
#include <d3d9.h>
#include "Component.h"
#include "IUpdateable.h"
#include "Transform.h"
#include "Time.h"

enum class Space { Global, Local };

class Mover : public Component, public IUpdateable
{
public:
	INT Init(Transform movement, Time* pTime);
	virtual void Update();
	virtual void DeInit();
	void SetSpace(Space relativeTo) { this->relativeTo = relativeTo; }

private:
	Transform movement;
	Time* pTime = nullptr;
	Space relativeTo;
};

