#pragma once
#include <vector>
#include "Transform.h"
#include "Component.h"

class GameObject
{
public:
	void DeInit();
	void AddComponent(Component* c);

	Transform transform {};
	std::vector<Component*> components = {};
};