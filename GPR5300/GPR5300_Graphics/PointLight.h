#pragma once
#include <d3d11.h>
#include "Component.h"
#include "IUpdateable.h"

struct PointLightData
{
	XMFLOAT3 position;
	FLOAT intensity;
	XMFLOAT4 color;
	FLOAT constantAttenuation;
	FLOAT linearAttenuation;
	FLOAT quadraticAttenuation;
	FLOAT maxDist;
};

class PointLight : public Component, public IUpdateable
{
public:
	//Initializes the PointLight with the given data values.
	INT Init(PointLightData lightData);
	//Updates the position of the PointLight.
	virtual void Update();
	virtual void DeInit();

	//Returns the PointLight Ddta.
	PointLightData GetData() { return data; }
private:
	PointLightData data = {};
};

