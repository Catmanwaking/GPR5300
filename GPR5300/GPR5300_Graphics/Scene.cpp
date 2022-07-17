#include <d3d9.h>
#include "Scene.h"
#include "GameObject.h"
#include "Mesh.h"
#include "Camera.h"
#include "Mover.h"
#include "Utils.h"

using namespace Constants;

INT Scene::Init(IDirect3DDevice9* pD3DDevice, UINT width, UINT height)
{
	this->pD3DDevice = pD3DDevice;
	INT error = 0;

	if (error = AddMeshes()) return error;
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

INT Scene::AddMeshes()
{
	GameObject* go = new GameObject;

	Mesh* pMesh = new Mesh;
	INT error = pMesh->Init(pD3DDevice);
	if (error) return error;
	renderables.push_back(dynamic_cast<IRenderable*>(pMesh));
	go->AddComponent(pMesh);

	Mover* pMover = new Mover;
	error = pMover->Init(Transform(0.0f, 0.0f, 0.0f, 0.12f * toRadian, 0.7f * toRadian, 0.3f * toRadian, 0.0f, 0.0f, 0.0f));
	if (error) return error;
	updateables.push_back(dynamic_cast<IUpdateable*>(pMover));
	go->AddComponent(pMover);

	gameObjects.push_back(go);

	return 0;
}

INT Scene::AddCamera(UINT width, UINT height)
{
	GameObject* go = new GameObject;

	Camera* pCamera = new Camera;
	INT error = pCamera->Init(pD3DDevice, width, height);
	if (error != 0)
		return error;
	updateables.push_back(dynamic_cast<IUpdateable*>(pCamera));
	go->AddComponent(pCamera);

	go->transform.position += Vector3(0.0f, 0.0f, -1.0f);
	gameObjects.push_back(go);

	return 0;
}
