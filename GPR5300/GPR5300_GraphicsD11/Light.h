#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

class Light
{
public:
	struct LightData
	{
		XMFLOAT3 direction;
		FLOAT intensity;
		XMFLOAT4 color;
	};

	INT Init(ID3D11Device* pD3DDevice, LightData& light, UINT id);
	void Render(ID3D11DeviceContext* pD3DDeviceContext);
	void DeInit();

private:
	UINT id = 0;
	LightData light = {};
	ID3D11Buffer* pLightBuffer = nullptr;
};

