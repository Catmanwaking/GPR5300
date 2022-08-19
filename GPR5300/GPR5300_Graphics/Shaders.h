#pragma once

namespace Shaders
{
	enum class Shader : int
	{
		Matte = 0,
		Glossy,
		NormalMapped,
		Water,
		Skybox,
	};

	const LPCWSTR vertexShaders[5] =
	{
		TEXT("Shaders\\MatteVertexShader.cso"),
		TEXT("Shaders\\GlossyVertexShader.cso"),
		TEXT("Shaders\\NormalMapVertexShader.cso"),
		TEXT("Shaders\\WaterVertexShader.cso"),
		TEXT("Shaders\\SkyboxVertexShader.cso")
	};

	const LPCWSTR pixelShaders[5] =
	{
		TEXT("Shaders\\MattePixelShader.cso"),
		TEXT("Shaders\\GlossyPixelShader.cso"),
		TEXT("Shaders\\NormalMapPixelShader.cso"),
		TEXT("Shaders\\WaterPixelShader.cso"),
		TEXT("Shaders\\SkyboxPixelShader.cso")
	};
}