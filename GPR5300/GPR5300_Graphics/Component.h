#pragma once
#include "Transform.h"

class Component
{
public:
	virtual void DeInit() {};
	void SetTransform(Transform* pTransform) { this->pTransform = pTransform; }

protected:
	Transform* pTransform;
};