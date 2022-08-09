#pragma once
#include <d3d11.h>

namespace Shaders
{
	enum Shader
	{
		LightShader = 0,
		SkyboxShader
	};

	const LPCWSTR vertexShaders[2] =
	{
		TEXT("LightVertexShader.cso"),
		TEXT("SkyboxVertexShader.cso")
	};

	const LPCWSTR pixelShaders[2] =
	{
		TEXT("LightPixelShader.cso"),
		TEXT("SkyboxPixelShader.cso")
	};
}