#pragma once
#include <d3d11.h>

namespace Shaders
{
	enum Shader
	{
		LightShader = 0,
		SkyboxShader,
		BrokenTextureShader
	};

	const LPCWSTR vertexShaders[3] =
	{
		TEXT("LightVertexShader.cso"),
		TEXT("SkyboxVertexShader.cso"),
		TEXT("TextureVertexShader.cso")
	};

	const LPCWSTR pixelShaders[3] =
	{
		TEXT("LightPixelShader.cso"),
		TEXT("SkyboxPixelShader.cso"),
		TEXT("TexturePixelShader.cso")
	};
}