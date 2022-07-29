#pragma once
#include <d3d9.h>

template <typename T>
inline void SafeRelease(T*& obj)
{
	if (obj != nullptr)
	{
		obj->Release();
		obj = nullptr;
	}
}

template <typename T>
inline void SafeClearAndDelete(T*& obj)
{
	if (obj != nullptr)
	{
		obj->clear();
		obj = nullptr;
	}
}