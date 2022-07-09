#pragma once
#include <d3d9.h>
#include <vector>
#include "GameObject.h"
#include "IRenderable.h"
#include "IUpdateable.h"

class Scene
{
public:
	INT Init(IDirect3DDevice9* pD3DDevice, UINT width, UINT height);
	void Update();
	void Render(IDirect3DDevice9* pD3DDevice);
	void DeInit();

private:
	std::vector<GameObject*> gameObjects = {};
	std::vector<IRenderable*> renderables = {};
	std::vector<IUpdateable*> updateables = {};
};

