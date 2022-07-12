#include <d3d9.h>
#include "Scene.h"
#include "GameObject.h"
#include "Mesh.h"
#include "Camera.h"

INT Scene::Init(IDirect3DDevice9* pD3DDevice, UINT width, UINT height)
{
	this->pD3DDevice = pD3DDevice;
	INT error = 0;

	if (error = AddMesh()) return error;
	if (error = AddCamera(width, height)) return error;

	return 0;
}

void Scene::Update()
{
	for (IUpdateable* updateObj : updateables)
	{
		updateObj->Update();
	}
}

void Scene::Render()
{
	for (IRenderable* renderObj : renderables)
	{
		renderObj->Render(pD3DDevice);
	}
}

void Scene::DeInit()
{
	for (GameObject* gameObj : gameObjects)
	{
		gameObj->DeInit();
	}
}

INT Scene::AddMesh()
{
	Mesh* mesh = new Mesh;
	INT error = mesh->Init(pD3DDevice);
	if (error != 0)
		return error;
	gameObjects.push_back(mesh);
	renderables.push_back(dynamic_cast<IRenderable*>(mesh));
	updateables.push_back(dynamic_cast<IUpdateable*>(mesh));
	return 0;
}

INT Scene::AddCamera(UINT width, UINT height)
{
	Camera* camera = new Camera;
	INT error = camera->Init(pD3DDevice, width, height);
	if (error != 0)
		return error;
	gameObjects.push_back(camera);
	updateables.push_back(dynamic_cast<IUpdateable*>(camera));
	return 0;
}
