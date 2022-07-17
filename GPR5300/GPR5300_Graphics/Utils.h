#pragma once
#include <d3d9.h>

namespace Constants
{
	constexpr float toRadian = 0.0174532925f;
}

template <typename T>
inline void SafeRelease(T*& obj)
{
	if (obj != nullptr)
	{
		obj->Release();
		obj = nullptr;
	}
}