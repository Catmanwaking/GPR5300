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
	float dissolve;
	float specularPower;
	XMFLOAT2 padding;
};

struct AdditionalData
{
	XMFLOAT4 data1;
	XMFLOAT4 data2;
	XMFLOAT4 data3;
	XMFLOAT4 data4;
};

class Material
{
public:
	//Initializes the Material alongside all buffers and shaders required for rendering.
	INT Init(ID3D11Device* pD3DDevice, std::string materialName, Shader shader);
	//Sets the required buffers and shaders for rendering
	void Render(ID3D11DeviceContext* pD3DDeviceContext, const XMMATRIX& rTransformationMatrix, const XMMATRIX& rViewProjectionMatrix);
	void DeInit();

	//Gets the pointer to the additional vertex shader buffer.
	AdditionalData* GetVSData() { return &pVSData; }
	//Gets the pointer to the additional pixel shader buffer.
	AdditionalData* GetPSData() { return &pPSData; }

protected:
	//Initializes the vertex shader.
	INT InitVertexShader(ID3D11Device* pD3DDevice, Shader shader);
	//Initializes the pixel shader.
	INT InitPixelShader(ID3D11Device* pD3DDevice, Shader shader);
	//Initializes the matrix buffer.
	INT InitMatrixBuffer(ID3D11Device* pD3DDevice);
	//Initializes the material buffer.
	INT InitMaterialBuffer(ID3D11Device* pD3DDevice, MaterialLoaderData* pMaterialData);
	//Initializes the texture shader resour.
	INT InitTextureAndSamplerState(ID3D11Device* pD3DDevice, std::string materialName);
	//Initializes the additional buffers.
	INT InitAdditionalBuffers(ID3D11Device* pD3DDevice);

	void SetMatrixBuffer(ID3D11DeviceContext* pD3DDeviceContext, const XMMATRIX& rTransformationMatrix, const XMMATRIX& rViewProjectionMatrix);
	void SetAdditionalBuffers(ID3D11DeviceContext* pD3DDeviceContext);

	ID3D11VertexShader* pVertexShader = nullptr;
	ID3D11PixelShader* pPixelShader = nullptr;
	ID3D11Buffer* pVSMatrixBuffer = nullptr;
	ID3D11Buffer* pPSMaterialBuffer = nullptr;
	ID3D11Buffer* pVSAdditionalBuffer = nullptr;
	ID3D11Buffer* pPSAdditionalBuffer = nullptr;

	ID3D11ShaderResourceView* pTexture = nullptr;
	ID3D11ShaderResourceView* pNormalMap = nullptr;
	ID3D11SamplerState* pSamplerState = nullptr;

	AdditionalData pVSData = {};
	AdditionalData pPSData = {};
};