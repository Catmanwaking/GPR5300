#pragma once
#include <d3d9.h>
#include <vector>
#include "GameObject.h"
#include "IRenderable.h"
#include "IUpdateable.h"
#include "Time.h"

class Scene
{
public:
	INT Init(IDirect3DDevice9* pD3DDevice, UINT width, UINT height);
	void Update();
	void Render();
	void DeInit();
	INT AddMeshes();
	INT AddCamera(UINT width, UINT height);

private:
	IDirect3DDevice9* pD3DDevice;
	std::vector<GameObject*> gameObjects = {};
	std::vector<IRenderable*> renderables = {};
	std::vector<IUpdateable*> updateables = {};

	Time time = {};
};

