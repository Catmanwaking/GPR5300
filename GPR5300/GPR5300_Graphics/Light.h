#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "DirectionalLight.h"
#include "PointLight.h"

using namespace DirectX;

struct LightData
{
	DirLightData dirLightBuffer; //size 48 byte all aligned
	PointLightData pointLight[8]; //size 48 * 8 byte all aligned
	XMFLOAT4 ambientLight;
	UINT pointLightCount; //4byte
	XMFLOAT3 padding;
};

class Light
{
public:	
	INT Init(ID3D11Device* pD3DDevice);
	void Render(ID3D11DeviceContext* pD3DDeviceContext);
	void DeInit();

	void AddLight(DirectionalLight* dDirLight);
	void AddLight(PointLight* pPointLight);

private:
	DirectionalLight* pDirLight = {};
	PointLight* pPointLights[8];
	XMFLOAT4 ambientLight = {};
	UINT pointLightCount = 0;

	ID3D11Buffer* pLightBuffer = nullptr;
};

