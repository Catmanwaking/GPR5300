#include <xutility>
#include <d3dcompiler.h>
#include "WICTextureLoader11.h"
#include "Material.h"
#include "Utils.h"

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;

INT Material::Init(ID3D11Device* pD3DDevice, LPCTSTR texturePath)
{
	INT error = InitVertexShader(pD3DDevice);
	if (error) return error;

	error = InitPixelShader(pD3DDevice);
	if (error) return error;

	//HRESULT hr = CreateWICTextureFromFile(pD3DDevice, texturePath, &pTexture, 0, WIC_LOADER_MIP_AUTOGEN);
	//if (FAILED(hr))
	//	return 50;

	//material.Ambient = { 1.0f, 1.0f, 1.0f, 1.0f };
	//material.Diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	//material.Specular = { 1.0f, 1.0f, 1.0f, 1.0f };
	//material.Power = 1024.0f;
	//material.Emissive = { 1.0f, 0.0f, 0.0f, 1.0f };

	return 0;
}

void Material::Render(ID3D11DeviceContext* pD3DDeviceContext)
{
	pD3DDeviceContext->IASetInputLayout(pInputLayout);
	pD3DDeviceContext->VSSetShader(pVertexShader,nullptr, 0);
	pD3DDeviceContext->PSSetShader(pPixelShader, nullptr, 0);

	//pD3DDevice->SetTexture(0, pTexture);
	//pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	//pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	//pD3DDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, D3DCOLOR_XRGB(255, 0, 255));
	//pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	//pD3DDevice->SetSamplerState(0, D3DSAMP_MAXMIPLEVEL, 0);
	//pD3DDevice->SetSamplerState(0, D3DSAMP_MIPMAPLODBIAS, 0);
	//pD3DDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 1);

	//pD3DDevice->SetMaterial(&material);
}

void Material::DeInit()
{
	//SafeRelease<IDirect3DTexture9>(pTexture);
	SafeRelease<ID3D11VertexShader>(pVertexShader);
	SafeRelease<ID3D11PixelShader>(pPixelShader);
	SafeRelease<ID3D11InputLayout>(pInputLayout);
}

INT Material::InitVertexShader(ID3D11Device* pD3DDevice)
{
	ID3DBlob* pCompiledShaderCode = nullptr;
	HRESULT hr = {};

	//hr = D3DCompileFromFile
	//(
	//	TEXT("ColorVertexShader.hlsl"),
	//	nullptr, nullptr,
	//	"main", "vs_4_0", 0, 0,
	//	&pCompiledShaderCode,
	//	nullptr
	//);
	hr = D3DReadFileToBlob(TEXT("ColorVertexShader.cso"), &pCompiledShaderCode);
	if (FAILED(hr)) return 50;

	hr = pD3DDevice->CreateVertexShader
	(
		pCompiledShaderCode->GetBufferPointer(),
		pCompiledShaderCode->GetBufferSize(),
		nullptr,
		&pVertexShader
	);
	if (FAILED(hr)) return 52;

	UINT error = InitInputLayot(pD3DDevice, pCompiledShaderCode);

	SafeRelease<ID3DBlob>(pCompiledShaderCode);

	return 0;
}

INT Material::InitPixelShader(ID3D11Device* pD3DDevice)
{
	ID3DBlob* pCompiledShaderCode = nullptr;
	HRESULT hr = {};

	hr = D3DReadFileToBlob(TEXT("ColorPixelShader.cso"), &pCompiledShaderCode);
	if (FAILED(hr)) return 54;

	hr = pD3DDevice->CreatePixelShader
	(
		pCompiledShaderCode->GetBufferPointer(),
		pCompiledShaderCode->GetBufferSize(),
		nullptr,
		&pPixelShader
	);
	if (FAILED(hr)) return 56;

	SafeRelease<ID3DBlob>(pCompiledShaderCode);

	return 0;
}

INT Material::InitInputLayot(ID3D11Device* pD3DDevice, ID3DBlob* pCompiledShaderCode)
{
	D3D11_INPUT_ELEMENT_DESC elementDescription[] =
	{
		{
			"POSITION", 0,
			DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
			D3D11_INPUT_PER_VERTEX_DATA, 0
		},		
	};
	D3D11_INPUT_ELEMENT_DESC elementDescriptions[4] = {};

	elementDescriptions[0].SemanticName = "POSITION";
	elementDescriptions[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;

	elementDescriptions[0].SemanticName = "NORMAL";
	elementDescriptions[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	elementDescriptions[0].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	elementDescriptions[0].SemanticName = "TEXCOORDS";
	elementDescriptions[0].Format = DXGI_FORMAT_R32G32_FLOAT;
	elementDescriptions[0].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	elementDescriptions[0].SemanticName = "COLOR";
	elementDescriptions[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	elementDescriptions[0].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	HRESULT hr = pD3DDevice->CreateInputLayout
	(
		elementDescription, 
		std::size(elementDescription), 
		pCompiledShaderCode->GetBufferPointer(),
		pCompiledShaderCode->GetBufferSize(), 
		&pInputLayout
	);

	if (FAILED(hr)) return 58;

	return 0;
}
