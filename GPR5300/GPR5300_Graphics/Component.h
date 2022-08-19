#pragma once
#include "Transform.h"

class Component
{
public:
	virtual void DeInit() {};
	//Sets the Transform reference from the GameObject this Component is attached to.
	void SetTransform(Transform* pTransform) { this->pTransform = pTransform; }

protected:
	Transform* pTransform = nullptr;
};