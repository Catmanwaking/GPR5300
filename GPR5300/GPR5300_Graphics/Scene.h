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

class Scene
{
public:
	INT Init(ID3D11Device* pD3DDevice, ID3D11DeviceContext* pDeviceContext, UINT width, UINT height);
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

	INT SetupCamera(UINT width, UINT height);
	INT AddLights(ID3D11Device* pD3DDevice);
	INT AddMeshes(ID3D11Device* pD3DDevice);

	INT AddCamera(GameObject* go, UINT width, UINT height);
	INT AddMesh(GameObject* go, ID3D11Device* pD3DDevice, std::string path);
	INT AddMover(GameObject* go, Vector3 movement);
	INT AddRotator(GameObject* go, Vector3 rotation);
	INT AddPlayerController(GameObject* go, UINT width, UINT height);
};