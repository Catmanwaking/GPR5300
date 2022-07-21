#pragma once
#include <d3d11.h>

class Material
{
public:
	INT Init(ID3D11Device* pD3DDevice, LPCTSTR texturePath);
	void Render(ID3D11DeviceContext* pD3DDeviceContext);
	void DeInit();

private:
	INT InitVertexShader(ID3D11Device* pD3DDevice);
	INT InitPixelShader(ID3D11Device* pD3DDevice);
	INT InitInputLayot(ID3D11Device* pD3DDevice, ID3DBlob* pCompiledShaderCode);

	ID3D11VertexShader* pVertexShader = nullptr;
	ID3D11PixelShader* pPixelShader = nullptr;
	ID3D11InputLayout* pInputLayout = nullptr;

	//IDirect3DTexture9* pTexture = nullptr;
	//D3DMATERIAL9 material = {};
};

