#include <d3d9.h>
#include "Scene.h"
#include "GameObject.h"
#include "Mesh.h"
#include "Camera.h"

INT Scene::Init(IDirect3DDevice9* pD3DDevice, UINT width, UINT height)
{
	Mesh* mesh = new Mesh;
	INT error = mesh->Init(pD3DDevice);
	if (error != 0)
		return error;
	gameObjects.push_back(mesh);
	renderables.push_back(dynamic_cast<IRenderable*>(mesh));
	updateables.push_back(dynamic_cast<IUpdateable*>(mesh));

	Camera* camera = new Camera;
	error = camera->Init(pD3DDevice, width, height);
	if (error != 0)
		return error;
	gameObjects.push_back(camera);
	updateables.push_back(dynamic_cast<IUpdateable*>(camera));

	return 0;
}

void Scene::Update()
{
	for (IUpdateable* updateObj : updateables)
	{
		updateObj->Update();
	}
}

void Scene::Render(IDirect3DDevice9* pD3DDevice)
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
