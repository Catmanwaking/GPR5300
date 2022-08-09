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
	INT Init(DirLightData lightData);
	virtual void Update();
	virtual void DeInit();

	DirLightData GetBuffer() { return data; }

private:
	DirLightData data = {};
};

