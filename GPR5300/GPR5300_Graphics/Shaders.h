#pragma once
#include <d3d11.h>

namespace Shaders
{
	enum Shader
	{
		Matte = 0,
		Glossy,
		NormalMapped,
		Skybox,
	};

	const LPCWSTR vertexShaders[4] =
	{
		TEXT("MatteVertexShader.cso"),
		TEXT("GlossyVertexShader.cso"),
		TEXT("NormalMapVertexShader.cso"),
		TEXT("SkyboxVertexShader.cso")
	};

	const LPCWSTR pixelShaders[4] =
	{
		TEXT("MattePixelShader.cso"),
		TEXT("GlossyPixelShader.cso"),
		TEXT("NormalMapPixelShader.cso"),
		TEXT("SkyboxPixelShader.cso")
	};
}