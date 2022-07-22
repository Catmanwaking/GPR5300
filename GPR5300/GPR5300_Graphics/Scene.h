#pragma once
#include <d3d9.h>
#include <vector>
#include <string>
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

private:
	IDirect3DDevice9* pD3DDevice = nullptr;
	std::vector<GameObject*> gameObjects = {};
	std::vector<IRenderable*> renderables = {};
	std::vector<IUpdateable*> updateables = {};

	Time* time = nullptr;

	INT SetupCamera(UINT width, UINT height);
	INT AddMeshes();

	INT AddCamera(GameObject* go, UINT width, UINT height);
	INT AddMesh(GameObject* go, std::string path);
	INT AddMover(GameObject* go, Vector3 movement);
	INT AddRotator(GameObject* go, Vector3 rotation);
};

