#pragma once
#include <vector>
#include "Transform.h"
#include "Component.h"

class GameObject
{
public:
	void DeInit();
	//Adds a component to the GameObject.
	void AddComponent(Component* c);

	Transform transform {};
	std::vector<Component*> components = {};
};