#include "WaterDataFiller.h"
#include "Time.h"
#include "Math.h"

void WaterDataFiller::Update()
{
	offset += Time::GetInstance()->GetDeltaTime() * waveSpeed; 

	pPSData->data1 = mainColor;
	pPSData->data2 = sideColor;
	pPSData->data3 = { fresnelPower, fresnelMult, 7.0f, 12.0f }; //fresnel pow, mult, tiling2
	pPSData->data4 = { offset, offset * waveCascadeSpeed, 0.0f, 0.0f }; //offset2, padding2
}

void WaterDataFiller::DeInit()
{
}
