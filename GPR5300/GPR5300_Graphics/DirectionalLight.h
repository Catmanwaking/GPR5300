#pragma once
#include <d3d11.h>
#include "Component.h"
#include "IUpdateable.h"

struct DirLightData
{
	XMFLOAT3 direction;
	FLOAT intensity;
	XMFLOAT4 color;
};

class DirectionalLight : public Component, public IUpdateable
{
public:
	//Initializes the DirectionalLight with the given data values.
	INT Init(DirLightData lightData);
	//Updates the rotation of the DirectionalLight.
	virtual void Update();
	virtual void DeInit();

	//Returns the DirectionalLight data.
	DirLightData GetData() { return data; }

private:
	DirLightData data = {};
};

