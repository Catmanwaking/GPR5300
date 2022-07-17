#include "GameObject.h"
#include "Utils.h"

void GameObject::DeInit()
{
	for (Component* component : components)
	{
		component->DeInit();
	}
	components.clear();
	components;
}

void GameObject::AddComponent(Component* c)
{
	c->SetTransform(&transform);
	components.push_back(c);
}
