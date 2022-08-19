#pragma once
#include <d3d11.h>
#include <vector>
#include <string>
#include "GameObject.h"
#include "IRenderable.h"
#include "IUpdateable.h"
#include "Camera.h"
#include "Time.h"
#include "Light.h"
#include "MeshGenerator.h"
#include "AdditionalDataFiller.h"
#include "Space.h"

class Scene
{
public:
	INT Init(ID3D11Device* pD3DDevice, ID3D11DeviceContext* pDeviceContext, ID3D11DepthStencilView* pDepthStencilView, UINT width, UINT height);
	void Update();
	void Render();
	void DeInit();

private:
	ID3D11DeviceContext* pD3DDeviceContext = nullptr;
	std::vector<GameObject*> gameObjects = {};
	std::vector<IRenderable*> renderables = {};
	std::vector<IUpdateable*> updateables = {};

	Camera* mainCam = nullptr;
	Time* pTime = nullptr;
	Light* pLight = nullptr;

	INT SetupCamera(ID3D11Device* pD3DDevice, ID3D11DepthStencilView* pDepthStencilView, UINT width, UINT height);
	INT AddLights(ID3D11Device* pD3DDevice);
	INT AddMeshes(ID3D11Device* pD3DDevice);

	INT AddCamera(GameObject* go, ID3D11Device* pD3DDevice, ID3D11DepthStencilView* pDepthStencilView, UINT width, UINT height);
	INT AddMesh(GameObject* go, ID3D11Device* pD3DDevice, std::string path, Shader shader, AdditionalDataFiller* pFiller);
	INT AddMesh(GameObject* go, ID3D11Device* pD3DDevice, Shape shape, Shader shader);
	INT AddMover(GameObject* go, Vector3 movement, Space space);
	INT AddSinWaveMover(GameObject* go, Vector3 movement, Vector3 anchor, FLOAT speed, Space space);
	INT AddRotator(GameObject* go, Vector3 rotation, Space space);
	INT AddPlayerController(GameObject* go);
	INT AddDirectionalLight(GameObject* go, DirLightData data);
	INT AddPointLight(GameObject* go, PointLightData data);
	INT AddAdditionalDataFiller(GameObject* go, AdditionalDataFiller* pFiller);
};