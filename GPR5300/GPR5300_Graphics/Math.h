#pragma once

namespace Constants
{
	const float toRadian = 0.0174532925f; //pi / 180
}

class Math
{
public:
	static float Clamp(float value, float min, float max);
};

