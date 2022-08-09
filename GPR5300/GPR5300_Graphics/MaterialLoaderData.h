#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <string>
#include <vector>

using namespace DirectX;

class MaterialLoaderData
{
public:
	XMFLOAT4 ambient;
	XMFLOAT4 diffuse;
	XMFLOAT4 specular;
	XMFLOAT4 emissive;
	FLOAT dissolve;
	FLOAT specularPower;

	std::wstring textureFileName;
};

