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
	INT Init(Vector3 movement);
	virtual void Update();
	virtual void DeInit();
	void SetSpace(Space relativeTo);

private:
	Vector3 movement = {};
	Time* pTime = nullptr;
	Space relativeTo = Space::Global;
};

