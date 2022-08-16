#include <d3d11.h>
#include "Scene.h"
#include "GameObject.h"
#include "Mesh.h"
#include "Mover.h"
#include "Rotator.h"
#include "PlayerController.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Utils.h"


using namespace Constants;

INT Scene::Init(ID3D11Device* pD3DDevice, ID3D11DeviceContext* pDeviceContext, ID3D11DepthStencilView* pDepthStencilView, UINT width, UINT height)
{
	this->pD3DDeviceContext = pDeviceContext;
	INT error = 0;

	pTime = Time::GetInstance();
	pTime->Init();

	if (error = SetupCamera(pD3DDevice, pDepthStencilView, width, height)) return error;
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
	mainCam->Render(pD3DDeviceContext);
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

INT Scene::SetupCamera(ID3D11Device* pD3DDevice, ID3D11DepthStencilView* pDepthStencilView, UINT width, UINT height)
{
	GameObject* go = new GameObject;

	AddCamera(go, pD3DDevice, pDepthStencilView, width, height, "skyBox");
	AddPlayerController(go);
	go->transform.position += Vector3(0.0f, 0.0f, -5.0f);

	gameObjects.push_back(go);

	return 0;
}

INT Scene::AddLights(ID3D11Device* pD3DDevice)
{
	pLight = new Light;
	INT error = pLight->Init(pD3DDevice);
	if (error) return error;

	GameObject* go = new GameObject;
	DirLightData dirLightData = {};
	dirLightData.direction = { 1.0f, -1.0f, 1.0f };
	dirLightData.color = { 0.0f, 1.0f, 1.0f, 1.0f };
	dirLightData.intensity = 1.0f;
	AddDirectionalLight(go, dirLightData);
	go->transform.rotation = Quaternion(Vector3(45.0f * toRadian, 45.0f * toRadian, 0.0f));

	go = new GameObject;
	PointLightData pointLightData = {};
	pointLightData.color = { 0.9843f, 0.2824f, 0.7686, 1.0f };
	pointLightData.intensity = 2.0f;
	pointLightData.constantAttenuation = 1.0f;
	pointLightData.linearAttenuation = 0.14f;
	pointLightData.quadraticAttenuation = 0.07f;
	pointLightData.maxDist = 10.0f;
	AddPointLight(go, pointLightData);
	AddRotator(go, Vector3(0.0f, 30.0f * toRadian,0.0f));
	AddMover(go, Vector3(3.0f, 0.0f, 0.0f));
	AddMesh(go, pD3DDevice, MeshGenerator::Shape::IcoSpehre, Shader::Matte);
	go->transform.position = Vector3(5.0f, 0.0f, 0.0f);
	go->transform.rotation = Quaternion(Vector3(0.0f, 90.0f * toRadian, 0.0f));
	go->transform.scale = Vector3(0.2f, 0.2f, 0.2f);

	return 0;
}

INT Scene::AddMeshes(ID3D11Device* pD3DDevice)
{
	//Opaque
	GameObject* go = new GameObject;
	AddMesh(go, pD3DDevice, "Cube", Shader::Matte);
	AddRotator(go, Vector3(30.0f * toRadian, 0.0f,0.0f));
	gameObjects.push_back(go);
	go->transform.rotation = Quaternion(Vector3(0.0f, 0.0f, XM_PIDIV4));
	go->transform.position = Vector3(0.0f, 4.0f, 0.0f);

	//go = new GameObject;
	//AddMesh(go, pD3DDevice, MeshGenerator::Shape::IcoSpehre, Shader::Matte);
	//gameObjects.push_back(go);
	//go->transform.position = Vector3(4.0f, 0.0f, 0.0f);

	go = new GameObject;
	AddMesh(go, pD3DDevice, "BrickWall", Shader::NormalMapped);
	gameObjects.push_back(go);

	go = new GameObject;
	AddMesh(go, pD3DDevice, "Water", Shader::Water);
	gameObjects.push_back(go);
	go->transform.position = Vector3(-10.0f, 0.0f, 0.0f);

	//transparent

	return 0;
}

INT Scene::AddCamera(GameObject* go, ID3D11Device* pD3DDevice, ID3D11DepthStencilView* pDepthStencilView, UINT width, UINT height, std::string skyBoxName)
{
	Camera* pCamera = new Camera;
	INT error = pCamera->Init(pD3DDevice, pDepthStencilView, width, height, skyBoxName, Shader::Skybox);
	if (error) return error;
	mainCam = pCamera;
	go->AddComponent(pCamera);

	return 0;
}

INT Scene::AddMesh(GameObject* go, ID3D11Device* pD3DDevice, std::string path, Shader shader)
{
	Mesh* pMesh = new Mesh;
	INT error = pMesh->Init(pD3DDevice, path, shader);
	if (error) return error;
	renderables.push_back(dynamic_cast<IRenderable*>(pMesh));
	go->AddComponent(pMesh);

	return 0;
}

INT Scene::AddMesh(GameObject* go, ID3D11Device* pD3DDevice, MeshGenerator::Shape shape, Shader shader)
{
	Mesh* pMesh = new Mesh;
	INT error = pMesh->Init(pD3DDevice, shape, shader);
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

INT Scene::AddPlayerController(GameObject* go)
{
	PlayerController* pController = new PlayerController;
	INT error = pController->Init();
	if (error) return error;
	updateables.push_back(dynamic_cast<IUpdateable*>(pController));
	go->AddComponent(pController);

	return 0;
}

INT Scene::AddDirectionalLight(GameObject* go, DirLightData data)
{
	DirectionalLight* pDirLight = new DirectionalLight;
	INT error = pDirLight->Init(data);
	if (error) return error;
	updateables.push_back(dynamic_cast<IUpdateable*>(pDirLight));
	pLight->AddLight(pDirLight);
	go->AddComponent(pDirLight);

	return 0;
}

INT Scene::AddPointLight(GameObject* go, PointLightData data)
{
	PointLight* pPointLight = new PointLight;
	INT error = pPointLight->Init(data);
	if (error) return error;
	updateables.push_back(dynamic_cast<IUpdateable*>(pPointLight));
	pLight->AddLight(pPointLight);
	go->AddComponent(pPointLight);

	return 0;
}
