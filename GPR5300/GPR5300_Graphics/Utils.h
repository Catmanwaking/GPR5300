#pragma once
#include <d3d9.h>

#define toRadian XM_PI / 180.0f

template <typename T>
inline void SafeRelease(T*& obj)
{
	if (obj != nullptr)
	{
		obj->Release();
		obj = nullptr;
	}
}