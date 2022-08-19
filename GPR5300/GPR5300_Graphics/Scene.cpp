#include <d3d11.h>
#include "Scene.h"
#include "GameObject.h"
#include "Mesh.h"
#include "Mover.h"
#include "SinWaveMover.h"
#include "Rotator.h"
#include "PlayerController.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "WaterDataFiller.h"
#include "Utils.h"

using namespace Constants;

INT Scene::Init(ID3D11Device* pD3DDevice, ID3D11DeviceContext* pDeviceContext, ID3D11DepthStencilView* pDepthStencilView, UINT width, UINT height)
{
	this->pD3DDeviceContext = pDeviceContext;
	INT error = 0;

	pTime = Time::GetInstance();
	if (error = pTime->Init()) return error;

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
	INT error = 0;

	GameObject* go = new GameObject;
	if (error = AddCamera(go, pD3DDevice, pDepthStencilView, width, height)) return error;
	if (error = AddPlayerController(go)) return error;
	go->transform.position += Vector3(0.0f, 0.0f, -10.0f);
	gameObjects.push_back(go);

	return 0;
}

INT Scene::AddLights(ID3D11Device* pD3DDevice)
{
	INT error = 0;
	pLight = new Light;
	if (error = pLight->Init(pD3DDevice)) return error;

	//directional light
	GameObject* go = new GameObject;
	DirLightData dirLightData = {};
	dirLightData.color = { 0.5f, 0.5f, 0.5f, 1.0f };
	dirLightData.intensity = 1.0f;
	if (error = AddDirectionalLight(go, dirLightData)) return error;
	go->transform.rotation = Quaternion::LookTo(Vector3(-1.0f, -1.0f, -1.0f));
	gameObjects.push_back(go);

	//pointlights
	//1 around link cube
	go = new GameObject;
	PointLightData pointLightData = {};
	pointLightData.color = { 0.9843f, 0.2824f, 0.7686f, 1.0f };
	pointLightData.intensity = 1.0f;
	pointLightData.constantAttenuation = 1.0f;
	pointLightData.linearAttenuation = 0.14f;
	pointLightData.quadraticAttenuation = 0.07f;
	pointLightData.maxDist = 15.0f;
	if (error = AddPointLight(go, pointLightData)) return error;
	if (error = AddRotator(go, Vector3(0.0f, 20.0f * toRadian,0.0f), Space::Global)) return error;
	if (error = AddMover(go, Vector3(1.0f, 0.0f, 0.0f), Space::Local)) return error;
	if (error = AddMesh(go, pD3DDevice, Shape::IcoSpehre, Shader::Matte)) return error;
	go->transform.position = Vector3(3.0f, 3.0f, 0.0f);
	go->transform.rotation = Quaternion(Vector3(0.0f, 90.0f * toRadian, 0.0f));
	go->transform.scale = Vector3(0.2f, 0.2f, 0.2f);
	gameObjects.push_back(go);

	//2 red in obamium cube
	go = new GameObject;
	pointLightData.color = { 0.8f, 0.0f, 0.0f, 1.0f };
	if (error = AddPointLight(go, pointLightData)) return error;
	if (error = AddRotator(go, Vector3(0.0f, 30.0f * toRadian, 0.0f), Space::Global)) return error;
	if (error = AddMover(go, Vector3(1.0f, 0.0f, 0.0f), Space::Local)) return error;
	if (error = AddMesh(go, pD3DDevice, Shape::Icosahedron, Shader::Glossy)) return error;
	go->transform.position = Vector3(30.0f, 3.0f, 32.5f);
	go->transform.scale = Vector3(0.2f, 0.4f, 0.2f);
	gameObjects.push_back(go);

	//3 green in obamium cube
	go = new GameObject;
	pointLightData.color = { 0.0f, 0.8f, 0.0f, 1.0f };
	if (error = AddPointLight(go, pointLightData)) return error;
	if (error = AddRotator(go, Vector3(-30.0f * toRadian, 0.0f, 0.0f), Space::Global)) return error;
	if (error = AddMover(go, Vector3(0.0f, 1.0f, 0.0f), Space::Local)) return error;
	if (error = AddMesh(go, pD3DDevice, Shape::Icosahedron, Shader::Glossy)) return error;
	go->transform.position = Vector3(32.5f, 0.0f, 32.5f);
	go->transform.scale = Vector3(0.4f, 0.2f, 0.2f);
	gameObjects.push_back(go);

	//4 close to water
	go = new GameObject;
	pointLightData.color = { 0.8f, 0.4f, 0.05f, 1.0f };
	if (error = AddPointLight(go, pointLightData)) return error;
	if (error = AddSinWaveMover(go, Vector3(-10.0f, 0.0f, 0.0f), Vector3(-5.0f, -10.5f, 0.0f), 0.5f, Space::Local)) return error;
	if (error = AddMesh(go, pD3DDevice, Shape::Icosahedron, Shader::Matte)) return error;
	go->transform.scale = Vector3(0.2f, 0.2f, 0.2f);
	gameObjects.push_back(go);

	//5 underneath normalmapped cubes
	go = new GameObject;
	pointLightData.color = { 0.8f, 0.8f, 0.8f, 1.0f };
	if (error = AddPointLight(go, pointLightData)) return error;
	if (error = AddSinWaveMover(go, Vector3(-3.0f, 0.0f, 0.0f), Vector3(-1.5f, -1.5f, 0.0f), 0.5f, Space::Local)) return error;
	if (error = AddMesh(go, pD3DDevice, Shape::Icosahedron, Shader::Matte)) return error;
	go->transform.scale = Vector3(0.2f, 0.2f, 0.2f);
	gameObjects.push_back(go);

	return 0;
}

INT Scene::AddMeshes(ID3D11Device* pD3DDevice)
{
	INT error = 0;

	//Opaque
	GameObject* go = new GameObject;
	if (error = AddMesh(go, pD3DDevice, "LinkCube", Shader::Matte, nullptr)) return error;
	if (error = AddRotator(go, Vector3(-30.0f * toRadian, 0.0f,0.0f), Space::Local)) return error;
	gameObjects.push_back(go);
	go->transform.rotation = Quaternion(Vector3(0.0f, 0.0f, 45.0f * toRadian));
	go->transform.position = Vector3(0.0f, 4.0f, 0.0f);

	go = new GameObject;
	AddMesh(go, pD3DDevice, Shape::IcoSpehre, Shader::Glossy);
	gameObjects.push_back(go);
	go->transform.position = Vector3(4.0f, 0.0f, 0.0f);

	go = new GameObject;
	if (error = AddMesh(go, pD3DDevice, "BrickWall", Shader::NormalMapped, nullptr)) return error;
	gameObjects.push_back(go);

	go = new GameObject;
	if (error = AddMesh(go, pD3DDevice, "BrickWall", Shader::Matte, nullptr)) return error;
	gameObjects.push_back(go);
	go->transform.position = Vector3(-2.5f, 0.0f, 0.0f);

	go = new GameObject;
	if (error = AddMesh(go, pD3DDevice, "Obamium", Shader::Matte, nullptr)) return error;
	if (error = AddRotator(go, Vector3(0.0f, -40.0f * toRadian, 0.0f), Space::Global)) return error;
	if (error = AddSinWaveMover(go, Vector3(0.0f, 0.4f, 0.0f), Vector3(30.0f, 0.0f, 30.0f), 3.0f,  Space::Global)) return error;
	gameObjects.push_back(go);

	go = new GameObject;
	if (error = AddMesh(go, pD3DDevice, "Cube", Shader::Matte, nullptr)) return error;
	if (error = AddRotator(go, Vector3(0.0f, 7.0f * toRadian, 0.0f), Space::Global)) return error;
	if (error = AddRotator(go, Vector3(0.0f, 0.0f, 5.0f * toRadian), Space::Local)) return error;
	gameObjects.push_back(go);
	go->transform.position = Vector3(30.0f, 0.0f, 30.0f);
	go->transform.scale = Vector3(5.0f, 5.0f, 5.0f);

	go = new GameObject;
	if (error = AddMesh(go, pD3DDevice, "Controls", Shader::Glossy, nullptr)) return error;
	gameObjects.push_back(go);
	go->transform.position = Vector3(-2.0f, 0.0f, -5.0f);
	go->transform.rotation = Quaternion(Vector3(-90.0f * toRadian, -45.0f * toRadian, 0.0f));

	//transparent
	go = new GameObject;
	WaterDataFiller* pFiller = new WaterDataFiller;
	if (error = AddAdditionalDataFiller(go, pFiller)) return error;
	if (error = AddMesh(go, pD3DDevice, "Water", Shader::Water, pFiller)) return error;
	gameObjects.push_back(go);
	go->transform.position = Vector3(0.0f, -11.0f, 0.0f);
	go->transform.scale = Vector3(10.0f, 1.0f, 10.0f);

	go = new GameObject;
	if (error = AddMesh(go, pD3DDevice, "RedPane", Shader::Glossy, nullptr)) return error;
	gameObjects.push_back(go);
	go->transform.position = Vector3(-4.0f, 4.0f, 1.0f);
	go->transform.rotation = Quaternion(Vector3(90.0f * toRadian, 0.0f, 0.0f));

	go = new GameObject;
	if (error = AddMesh(go, pD3DDevice, "BluePane", Shader::Glossy, nullptr)) return error;
	gameObjects.push_back(go);
	go->transform.position = Vector3(-4.0f, 4.0f, 0.0f);
	go->transform.rotation = Quaternion(Vector3(90.0f * toRadian, 0.0f, 0.0f));

	go = new GameObject;
	if (error = AddMesh(go, pD3DDevice, "GreenPane", Shader::Glossy, nullptr)) return error;
	gameObjects.push_back(go);
	go->transform.position = Vector3(-4.0f, 4.0f, -1.0f);
	go->transform.rotation = Quaternion(Vector3(90.0f * toRadian, 0.0f, 0.0f));

	return 0;
}

#pragma region AddFunctions

INT Scene::AddCamera(GameObject* go, ID3D11Device* pD3DDevice, ID3D11DepthStencilView* pDepthStencilView, UINT width, UINT height)
{
	Camera* pCamera = new Camera;
	if (INT error = pCamera->Init(pD3DDevice, pDepthStencilView, width, height)) return error;
	mainCam = pCamera;
	go->AddComponent(pCamera);

	return 0;
}

INT Scene::AddMesh(GameObject* go, ID3D11Device* pD3DDevice, std::string path, Shader shader, AdditionalDataFiller* pFiller)
{
	Mesh* pMesh = new Mesh;
	if (INT error = pMesh->Init(pD3DDevice, path, shader)) return error;
	renderables.push_back(dynamic_cast<IRenderable*>(pMesh));
	go->AddComponent(pMesh);

	if (pFiller != nullptr)
		pFiller->SetMaterial(pMesh->GetMaterial());

	return 0;
}

INT Scene::AddMesh(GameObject* go, ID3D11Device* pD3DDevice, Shape shape, Shader shader)
{
	Mesh* pMesh = new Mesh;
	if (INT error = pMesh->Init(pD3DDevice, shape, shader)) return error;
	renderables.push_back(dynamic_cast<IRenderable*>(pMesh));
	go->AddComponent(pMesh);

	return 0;
}

INT Scene::AddMover(GameObject* go, Vector3 movement, Space space)
{
	Mover* pMover = new Mover;
	if (INT error = pMover->Init(movement)) return error;
	pMover->SetSpace(space);
	updateables.push_back(dynamic_cast<IUpdateable*>(pMover));
	go->AddComponent(pMover);

	return 0;
}

INT Scene::AddSinWaveMover(GameObject* go, Vector3 movement, Vector3 anchor, FLOAT speed, Space space)
{
	SinWaveMover* pMover = new SinWaveMover;
	if (INT error = pMover->Init(movement, anchor, speed)) return error;
	pMover->SetSpace(space);
	updateables.push_back(dynamic_cast<IUpdateable*>(pMover));
	go->AddComponent(pMover);

	return 0;
}

INT Scene::AddRotator(GameObject* go, Vector3 rotation, Space space)
{
	Rotator* pRotator = new Rotator;
	if (INT error = pRotator->Init(rotation)) return error;
	pRotator->SetSpace(space);
	updateables.push_back(dynamic_cast<IUpdateable*>(pRotator));
	go->AddComponent(pRotator);

	return 0;
}

INT Scene::AddPlayerController(GameObject* go)
{
	PlayerController* pController = new PlayerController;
	if (INT error = pController->Init()) return error;
	updateables.push_back(dynamic_cast<IUpdateable*>(pController));
	go->AddComponent(pController);

	return 0;
}

INT Scene::AddDirectionalLight(GameObject* go, DirLightData data)
{
	DirectionalLight* pDirLight = new DirectionalLight;
	if (INT error = pDirLight->Init(data)) return error;
	updateables.push_back(dynamic_cast<IUpdateable*>(pDirLight));
	pLight->AddLight(pDirLight);
	go->AddComponent(pDirLight);

	return 0;
}

INT Scene::AddPointLight(GameObject* go, PointLightData data)
{
	PointLight* pPointLight = new PointLight;
	if (INT error = pPointLight->Init(data)) return error;
	updateables.push_back(dynamic_cast<IUpdateable*>(pPointLight));
	pLight->AddLight(pPointLight);
	go->AddComponent(pPointLight);

	return 0;
}

INT Scene::AddAdditionalDataFiller(GameObject* go, AdditionalDataFiller* pFiller)
{
	if (INT error = pFiller->Init()) return error;
	updateables.push_back(dynamic_cast<IUpdateable*>(pFiller));
	go->AddComponent(pFiller);

	return 0;
}

#pragma endregion
