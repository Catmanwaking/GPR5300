#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <string>
#include "MeshData.h"

using namespace DirectX;

class Material
{
public:
	INT Init(ID3D11Device* pD3DDevice, std::string materialName);
	void Render(ID3D11DeviceContext* pD3DDeviceContext, const XMMATRIX& rTransformationMatrix, const XMMATRIX& rViewProjectionMatrix);
	void DeInit();

private:
	INT InitVertexShader(ID3D11Device* pD3DDevice);
	INT InitPixelShader(ID3D11Device* pD3DDevice);
	INT InitInputLayot(ID3D11Device* pD3DDevice, ID3DBlob* pCompiledShaderCode);
	INT InitMatrixBuffer(ID3D11Device* pD3DDevice);
	INT InitTextureAndSamplerState(ID3D11Device* pD3DDevice, std::string materialName);

	void SetMatrixBuffer(ID3D11DeviceContext* pD3DDeviceContext, const XMMATRIX& rTransformationMatrix, const XMMATRIX& rViewProjectionMatrix);

	ID3D11VertexShader* pVertexShader = nullptr;
	ID3D11PixelShader* pPixelShader = nullptr;
	ID3D11InputLayout* pInputLayout = nullptr;
	ID3D11Buffer* pMatrixBuffer = nullptr;
	struct MatrixBuffer
	{
		XMFLOAT4X4 worldViewProjectionMatrix;
		XMFLOAT4X4 worldMatrix;
	};

	ID3D11ShaderResourceView* pTexture = nullptr;
	ID3D11SamplerState* pSamplerState = nullptr;
};

