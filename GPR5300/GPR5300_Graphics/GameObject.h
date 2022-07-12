#pragma once
#include <DirectXMath.h>
#include <d3d9.h>
#include "Transform.h"

using namespace DirectX;

class GameObject
{
public:
	virtual void DeInit() {};
	Transform transform {};
	GameObject(Transform transform) { this->transform = transform; }
};