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

	error = InitMatrixBuffer(pD3DDevice);
	if (error) return error;

	error = InitTextureAndSamplerState(pD3DDevice, texturePath);
	if (error) return error;

	//material.Ambient = { 1.0f, 1.0f, 1.0f, 1.0f };
	//material.Diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	//material.Specular = { 1.0f, 1.0f, 1.0f, 1.0f };
	//material.Power = 1024.0f;
	//material.Emissive = { 1.0f, 0.0f, 0.0f, 1.0f };

	return 0;
}

void Material::Render(ID3D11DeviceContext* pD3DDeviceContext, const XMFLOAT4X4& rWorldMatrix, const XMFLOAT4X4& rViewMatrix, const XMFLOAT4X4& rProjectionMatrix)
{
	pD3DDeviceContext->IASetInputLayout(pInputLayout);
	pD3DDeviceContext->VSSetShader(pVertexShader,nullptr, 0);
	pD3DDeviceContext->PSSetShader(pPixelShader, nullptr, 0);

	SetMatrixBuffer(pD3DDeviceContext, rWorldMatrix, rViewMatrix, rProjectionMatrix);

	pD3DDeviceContext->PSSetShaderResources(0, 1, &pTexture);
	pD3DDeviceContext->PSSetSamplers(0, 1, &pSamplerState);
}

void Material::DeInit()
{
	SafeRelease<ID3D11SamplerState>(pSamplerState);
	SafeRelease<ID3D11ShaderResourceView>(pTexture);
	SafeRelease<ID3D11Buffer>(pMatrixBuffer);
	SafeRelease<ID3D11InputLayout>(pInputLayout);
	SafeRelease<ID3D11PixelShader>(pPixelShader);
	SafeRelease<ID3D11VertexShader>(pVertexShader);
}

INT Material::InitVertexShader(ID3D11Device* pD3DDevice)
{
	ID3DBlob* pCompiledShaderCode = nullptr;
	HRESULT hr = {};

	//hr = D3DReadFileToBlob(TEXT("ColorVertexShader.cso"), &pCompiledShaderCode);
	//hr = D3DReadFileToBlob(TEXT("TextureVertexShader.cso"), &pCompiledShaderCode);
	hr = D3DReadFileToBlob(TEXT("LightVertexShader.cso"), &pCompiledShaderCode);

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

	//hr = D3DReadFileToBlob(TEXT("ColorPixelShader.cso"), &pCompiledShaderCode);
	//hr = D3DReadFileToBlob(TEXT("TexturePixelShader.cso"), &pCompiledShaderCode);
	hr = D3DReadFileToBlob(TEXT("LightPixelShader.cso"), &pCompiledShaderCode);
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
	D3D11_INPUT_ELEMENT_DESC elementDescriptions[4] = {};

	elementDescriptions[0].SemanticName = "POSITION";
	elementDescriptions[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;

	elementDescriptions[1].SemanticName = "NORMAL";
	elementDescriptions[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	elementDescriptions[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	elementDescriptions[2].SemanticName = "TEXCOORD";
	elementDescriptions[2].Format = DXGI_FORMAT_R32G32_FLOAT;
	elementDescriptions[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	elementDescriptions[3].SemanticName = "COLOR";
	elementDescriptions[3].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	elementDescriptions[3].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	HRESULT hr = pD3DDevice->CreateInputLayout
	(
		elementDescriptions, 
		std::size(elementDescriptions), 
		pCompiledShaderCode->GetBufferPointer(),
		pCompiledShaderCode->GetBufferSize(), 
		&pInputLayout
	);

	if (FAILED(hr)) return 58;

	return 0;
}

INT Material::InitMatrixBuffer(ID3D11Device* pD3DDevice)
{
	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = sizeof(MatrixBuffer);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HRESULT hr = pD3DDevice->CreateBuffer(&desc, nullptr, &pMatrixBuffer);
	if (FAILED(hr)) return 51;

	return 0;
}

INT Material::InitTextureAndSamplerState(ID3D11Device* pD3DDevice, LPCTSTR texturePath)
{
	HRESULT hr = CreateWICTextureFromFile(pD3DDevice, texturePath, nullptr, &pTexture);
	if (FAILED(hr)) return 53;

	D3D11_SAMPLER_DESC desc = {};
	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;

	hr = pD3DDevice->CreateSamplerState(&desc, &pSamplerState);
	if (FAILED(hr)) return 55;

	return 0;
}

void Material::SetMatrixBuffer(ID3D11DeviceContext* pD3DDeviceContext, const XMFLOAT4X4& rWorldMatrix, const XMFLOAT4X4& rViewMatrix, const XMFLOAT4X4& rProjectionMatrix)
{
	XMMATRIX worldMatrix = XMLoadFloat4x4(&rWorldMatrix);
	XMMATRIX viewMatrix = XMLoadFloat4x4(&rViewMatrix);
	XMMATRIX projectionMatrix = XMLoadFloat4x4(&rProjectionMatrix);
	
	XMMATRIX worldViewProjectionMatrix = XMMatrixTranspose(worldMatrix * viewMatrix * projectionMatrix);

	D3D11_MAPPED_SUBRESOURCE data = {};
	HRESULT hr = pD3DDeviceContext->Map(pMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
	if (FAILED(hr)) return;

	MatrixBuffer* matrixBuffer = static_cast<MatrixBuffer*>(data.pData);

	XMStoreFloat4x4(&matrixBuffer->worldViewProjectionMatrix, worldViewProjectionMatrix); //TODO maybe wrong &
	XMStoreFloat4x4(&matrixBuffer->worldMatrix, XMMatrixTranspose(worldMatrix));

	pD3DDeviceContext->Unmap(pMatrixBuffer, 0);

	pD3DDeviceContext->VSSetConstantBuffers(0, 1, &pMatrixBuffer);
}
