#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

class Material
{
public:
	INT Init(ID3D11Device* pD3DDevice, LPCTSTR texturePath);
	void Render(ID3D11DeviceContext* pD3DDeviceContext, const XMFLOAT4X4& rWorldMatrix, const XMFLOAT4X4& rViewMatrix, const XMFLOAT4X4& rProjectionMatrix);
	void DeInit();

private:
	INT InitVertexShader(ID3D11Device* pD3DDevice);
	INT InitPixelShader(ID3D11Device* pD3DDevice);
	INT InitInputLayot(ID3D11Device* pD3DDevice, ID3DBlob* pCompiledShaderCode);
	INT InitMatrixBuffer(ID3D11Device* pD3DDevice);
	INT InitTextureAndSamplerState(ID3D11Device* pD3DDevice, LPCTSTR texturePath);

	void SetMatrixBuffer(ID3D11DeviceContext* pD3DDeviceContext, const  XMFLOAT4X4& rWorldMatrix, const XMFLOAT4X4& rViewMatrix, const XMFLOAT4X4& rProjectionMatrix);

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

	//D3DMATERIAL9 material = {};
};

