#pragma once
#include <d3d9.h>
#include <DirectXMath.h>
#include <string>
#include <vector>

using namespace DirectX;

class MaterialData
{
public:
	D3DCOLORVALUE ambient;
	D3DCOLORVALUE diffuse;
	D3DCOLORVALUE specular;
	D3DCOLORVALUE emissive;
	float dissolve;
	float specularPower;

	std::wstring textureFileName;
};

