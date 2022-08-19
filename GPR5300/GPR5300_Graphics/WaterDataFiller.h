#pragma once
#include <d3d11.h>
#include "AdditionalDataFiller.h"

class WaterDataFiller : public AdditionalDataFiller
{
public:
	//Writes the data needed for the water shader to the linked additional data pointer.
	virtual void Update();
	virtual void DeInit();

private:
	float offset = 0.0f;
	XMFLOAT4 mainColor = { 0.0235f, 0.0f, 0.2f, 1.0f };
	XMFLOAT4 sideColor = { 0.0f, 0.8f, 0.8f, 1.0f };
	XMFLOAT2 tiling = { 7.0f, 12.0f };

	float fresnelPower = 4.2f;
	float fresnelMult = 2.5f;
	float waveSpeed = 0.04f;
	float waveCascadeSpeed = 0.4f;
};

