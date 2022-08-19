#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

namespace Constants
{
	const float toRadian = XM_PI / 180.0f;
	const float goldenRatio = (1.0f + sqrtf(5.0f)) / 2.0f;
}

class Math
{
public:
	//Clamps the input between min and max.
	static float Clamp(float value, float min, float max);
};

