#pragma once
#include <d3d9.h>
#include "Component.h"
#include "IUpdateable.h"
#include "Transform.h"

class Mover : public Component, public IUpdateable
{
public:
	INT Init(Transform movement);
	virtual void Update();
	virtual void DeInit();

private:
	Transform movement;
};

