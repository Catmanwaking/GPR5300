#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <string>
#include "MaterialLoaderData.h"
#include "Shaders.h"

using namespace Shaders;

struct MatrixBuffer
{
	XMFLOAT4X4 worldViewProjectionMatrix;
	XMFLOAT4X4 worldMatrix;
};

struct MaterialData
{
	FLOAT dissolve;
	FLOAT specularPower;
};

class Material
{
public:
	INT Init(ID3D11Device* pD3DDevice, std::string materialName, Shader shader);
	virtual void Render(ID3D11DeviceContext* pD3DDeviceContext, const XMMATRIX& rTransformationMatrix, const XMMATRIX& rViewProjectionMatrix);
	virtual void DeInit();

protected:
	INT InitVertexShader(ID3D11Device* pD3DDevice, Shader shader);
	INT InitPixelShader(ID3D11Device* pD3DDevice, Shader shader);
	INT InitMatrixBuffer(ID3D11Device* pD3DDevice);
	INT InitMaterialBuffer(ID3D11Device* pD3DDevice, MaterialLoaderData* pMaterialData);
	INT InitTextureAndSamplerState(ID3D11Device* pD3DDevice, std::string materialName);
	virtual INT InitAdditionalBuffers(ID3D11Device* pD3DDevice) { return 0; }

	virtual void SetMatrixBuffer(ID3D11DeviceContext* pD3DDeviceContext, const XMMATRIX& rTransformationMatrix, const XMMATRIX& rViewProjectionMatrix);
	virtual void SetAdditionalBuffers(ID3D11DeviceContext* pD3DDeviceContext) {}

	ID3D11VertexShader* pVertexShader = nullptr;
	ID3D11PixelShader* pPixelShader = nullptr;
	ID3D11InputLayout* pInputLayout = nullptr;
	ID3D11Buffer* pMatrixBuffer = nullptr;
	ID3D11Buffer* pMaterialBuffer = nullptr;

	ID3D11ShaderResourceView* pTexture = nullptr;
	ID3D11ShaderResourceView* pNormalMap = nullptr;
	ID3D11SamplerState* pSamplerState = nullptr;
};