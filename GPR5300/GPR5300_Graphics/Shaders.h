#pragma once

namespace Shaders
{
	enum Shader
	{
		Matte = 0,
		Glossy,
		NormalMapped,
		Water,
		Skybox,
	};

	const LPCWSTR vertexShaders[5] =
	{
		TEXT("MatteVertexShader.cso"),
		TEXT("GlossyVertexShader.cso"),
		TEXT("NormalMapVertexShader.cso"),
		TEXT("WaterVertexShader.cso"),
		TEXT("SkyboxVertexShader.cso")
	};

	const LPCWSTR pixelShaders[5] =
	{
		TEXT("MattePixelShader.cso"),
		TEXT("GlossyPixelShader.cso"),
		TEXT("NormalMapPixelShader.cso"),
		TEXT("WaterPixelShader.cso"),
		TEXT("SkyboxPixelShader.cso")
	};
}