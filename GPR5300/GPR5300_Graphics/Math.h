#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

namespace Constants
{
	const float toRadian = 0.0174532925f; //pi / 180
	const float goldenRatio = 1.6180339887f; //(1.0 + Sqrt(5)) / 2.0
}

class Math
{
public:
	static float Clamp(float value, float min, float max);
};

