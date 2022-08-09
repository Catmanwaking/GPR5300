#pragma once
#include <d3d11.h>
#include "Component.h"
#include "IUpdateable.h"

struct PointLightData
{
	XMFLOAT3 position;
	FLOAT intensity;
	XMFLOAT4 color;
};

class PointLight : public Component, public IUpdateable
{
public:
	INT Init(PointLightData lightData);
	virtual void Update();
	virtual void DeInit();

	PointLightData GetBuffer() { return data; }
private:
	PointLightData data = {};
};

