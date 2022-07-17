#pragma once
#include <d3d9.h>
#include "Vector3.h"
#include "Component.h"
#include "IUpdateable.h"
#include "Time.h"
#include "Space.h"

class Rotator : public Component, public IUpdateable
{
public:
	INT Init(Vector3 rotation, Time* pTime);
	virtual void Update();
	virtual void DeInit();
	void SetSpace(Space relativeTo);

private:
	Vector3 rotation = {};
	Time* pTime = nullptr;
	Space relativeTo = Space::Global;
};

