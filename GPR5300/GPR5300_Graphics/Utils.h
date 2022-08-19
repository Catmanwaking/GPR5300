#pragma once
#include <d3d11.h>

//Safely releases DirectX related data.
template <typename T>
inline void SafeRelease(T*& obj)
{
	if (obj != nullptr)
	{
		obj->Release();
		obj = nullptr;
	}
}

//Clears and Deletes a std::vector collection.
template <typename T>
inline void SafeClearAndDelete(T*& obj)
{
	if (obj != nullptr)
	{
		obj->clear();
		obj = nullptr;
	}
}