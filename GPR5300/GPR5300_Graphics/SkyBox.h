#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <string>
#include "MeshData.h"

using namespace DirectX;

class SkyBox
{
public:
	INT Init(ID3D11Device* pD3DDevice, std::string skyBoxName);
	void Render(ID3D11DeviceContext* pD3DDeviceContext, const XMMATRIX& rViewProjectionMatrix);
	void DeInit();

private:
	INT InitVertexBuffer(ID3D11Device* pD3DDevice);
	INT InitIndexBuffer(ID3D11Device* pD3DDevice);

	INT InitVertexShader(ID3D11Device* pD3DDevice);
	INT InitPixelShader(ID3D11Device* pD3DDevice);
	INT InitInputLayot(ID3D11Device* pD3DDevice, ID3DBlob* pCompiledShaderCode);
	INT InitMatrixBuffer(ID3D11Device* pD3DDevice);
	INT InitTextureAndSamplerState(ID3D11Device* pD3DDevice, std::string materialName);

	void SetMatrixBuffer(ID3D11DeviceContext* pD3DDeviceContext, const XMMATRIX& rViewProjectionMatrix);

	ID3D11Buffer* pVertexBuffer = nullptr;
	ID3D11Buffer* pIndexBuffer = nullptr;

	USHORT vertexCount = 0;
	UINT vertexStride = 0;
	UINT indexCount = 0;

	MeshData* pMeshData = nullptr;

	ID3D11VertexShader* pVertexShader = nullptr;
	ID3D11PixelShader* pPixelShader = nullptr;
	ID3D11InputLayout* pInputLayout = nullptr;
	ID3D11Buffer* pMatrixBuffer = nullptr;
	struct MatrixBuffer
	{
		XMFLOAT4X4 viewProjectionMatrix;
	};

	ID3D11ShaderResourceView* pTexture = nullptr;
	ID3D11SamplerState* pSamplerState = nullptr;
};

