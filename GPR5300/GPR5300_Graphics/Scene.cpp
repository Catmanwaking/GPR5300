#include <d3d11.h>
#include "Scene.h"
#include "GameObject.h"
#include "Mesh.h"
#include "Mover.h"
#include "Rotator.h"
#include "PlayerController.h"
#include "Utils.h"

using namespace Constants;

INT Scene::Init(ID3D11Device* pD3DDevice, ID3D11DeviceContext* pDeviceContext, UINT width, UINT height)
{
	this->pD3DDeviceContext = pDeviceContext;
	INT error = 0;

	pTime = Time::GetInstance();
	pTime->Init();

	if (error = SetupCamera(width, height)) return error;
	if (error = AddLights(pD3DDevice)) return error;
	if (error = AddMeshes(pD3DDevice)) return error;

	return 0;
}

void Scene::Update()
{
	pTime->Update();
	for (IUpdateable* updateObj : updateables)
	{
		updateObj->Update();
	}
}

void Scene::Render()
{
	pLight->Render(pD3DDeviceContext);
	for (IRenderable* renderObj : renderables)
	{
		renderObj->Render(pD3DDeviceContext, mainCam->GetViewProjectionMatrix());
	}
}

void Scene::DeInit()
{
	for (GameObject* gameObj : gameObjects)
	{
		gameObj->DeInit();
	}
	pTime->DeInit();
}

INT Scene::SetupCamera(UINT width, UINT height)
{
	GameObject* go = new GameObject;

	AddCamera(go, width, height);
	AddPlayerController(go, width, height);
	go->transform.position += Vector3(0.0f, 0.0f, -5.0f);

	gameObjects.push_back(go);

	return 0;
}

INT Scene::AddLights(ID3D11Device* pD3DDevice)
{
	Light::LightData lightData = {};
	lightData.direction = { 1.0f, -1.0f, 1.0f };
	lightData.color = { 1.0f, 1.0f, 1.0f, 1.0f };
	lightData.intensity = 1.0f;

	pLight = new Light();
	INT error = pLight->Init(pD3DDevice, lightData, 0);
	if (error) return error;

	return 0;
}

INT Scene::AddMeshes(ID3D11Device* pD3DDevice)
{
	GameObject* go = new GameObject;

	AddMesh(go, pD3DDevice, "Cube");
	AddRotator(go, Vector3(30.0f * toRadian, 0.0f,0.0f));
	//AddMover(go, Vector3(3.0f, 0.0f, 0.0f));

	gameObjects.push_back(go);

	go->transform.rotation = Quaternion(Vector3(0.0f, 0.0f, XM_PIDIV4));

	return 0;
}

INT Scene::AddCamera(GameObject* go, UINT width, UINT height)
{
	Camera* pCamera = new Camera;
	INT error = pCamera->Init(width, height);
	if (error) return error;
	updateables.push_back(dynamic_cast<IUpdateable*>(pCamera));
	go->AddComponent(pCamera);

	mainCam = pCamera;

	return 0;
}

INT Scene::AddMesh(GameObject* go, ID3D11Device* pD3DDevice, std::string path)
{
	Mesh* pMesh = new Mesh;
	INT error = pMesh->Init(pD3DDevice, path);
	if (error) return error;
	renderables.push_back(dynamic_cast<IRenderable*>(pMesh));

	go->AddComponent(pMesh);

	return 0;
}

INT Scene::AddMover(GameObject* go, Vector3 movement)
{
	Mover* pMover = new Mover;
	INT error = pMover->Init(movement);
	if (error) return error;
	pMover->SetSpace(Space::Local);
	updateables.push_back(dynamic_cast<IUpdateable*>(pMover));
	go->AddComponent(pMover);

	return 0;
}

INT Scene::AddRotator(GameObject* go, Vector3 rotation)
{
	Rotator* pRotator = new Rotator;
	INT error = pRotator->Init(rotation);
	if (error) return error;
	pRotator->SetSpace(Space::Local);
	updateables.push_back(dynamic_cast<IUpdateable*>(pRotator));
	go->AddComponent(pRotator);

	return 0;
}

INT Scene::AddPlayerController(GameObject* go, UINT width, UINT height)
{
	PlayerController* pController = new PlayerController;
	INT error = pController->Init(width, height);
	if (error) return error;
	updateables.push_back(dynamic_cast<IUpdateable*>(pController));
	go->AddComponent(pController);

	return 0;
}
