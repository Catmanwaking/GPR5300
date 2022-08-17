#include "Material.h"
#include <d3dcompiler.h>
#include <xutility>
#include "WICTextureLoader11.h"
#include "Utils.h"
#include "MaterialLoaderData.h"
#include "MaterialLoader.h"

#pragma comment(lib, "d3dcompiler.lib")

INT Material::Init(ID3D11Device* pD3DDevice, std::string materialName, Shader shader)
{
	INT error = InitVertexShader(pD3DDevice, shader);
	if (error) return error;

	error = InitPixelShader(pD3DDevice, shader);
	if (error) return error;

	error = InitMatrixBuffer(pD3DDevice);
	if (error) return error;

	error = InitAdditionalBuffers(pD3DDevice);
	if (error) return error;

	error = InitTextureAndSamplerState(pD3DDevice, materialName);
	if (error) return error;

	return 0;
}

void Material::Render(ID3D11DeviceContext* pD3DDeviceContext, const XMMATRIX& rTransformationMatrix, const XMMATRIX& rViewProjectionMatrix)
{
	pD3DDeviceContext->VSSetShader(pVertexShader, nullptr, 0);
	pD3DDeviceContext->PSSetShader(pPixelShader, nullptr, 0);

	SetMatrixBuffer(pD3DDeviceContext, rTransformationMatrix, rViewProjectionMatrix);
	SetAdditionalBuffers(pD3DDeviceContext);
	pD3DDeviceContext->PSSetConstantBuffers(1, 1, &pPSMaterialBuffer);
	pD3DDeviceContext->PSSetShaderResources(0, 1, &pTexture);
	if(pNormalMap != nullptr)
		pD3DDeviceContext->PSSetShaderResources(1, 1, &pNormalMap);

	pD3DDeviceContext->PSSetSamplers(0, 1, &pSamplerState);
}

void Material::DeInit()
{
	SafeRelease<ID3D11SamplerState>(pSamplerState);
	SafeRelease<ID3D11ShaderResourceView>(pTexture);
	SafeRelease<ID3D11Buffer>(pVSMatrixBuffer);
	SafeRelease<ID3D11Buffer>(pPSMaterialBuffer);
	SafeRelease<ID3D11Buffer>(pVSAdditionalBuffer);
	SafeRelease<ID3D11Buffer>(pPSAdditionalBuffer);
	SafeRelease<ID3D11PixelShader>(pPixelShader);
	SafeRelease<ID3D11VertexShader>(pVertexShader);
}

INT Material::InitVertexShader(ID3D11Device* pD3DDevice, Shader shader)
{
	ID3DBlob* pCompiledShaderCode = nullptr;
	HRESULT hr = {};

	LPCWSTR path = vertexShaders[shader];
	hr = D3DReadFileToBlob(vertexShaders[shader], &pCompiledShaderCode);
	if (FAILED(hr)) return 50;

	hr = pD3DDevice->CreateVertexShader
	(
		pCompiledShaderCode->GetBufferPointer(),
		pCompiledShaderCode->GetBufferSize(),
		nullptr,
		&pVertexShader
	);
	if (FAILED(hr)) return 52;

	SafeRelease<ID3DBlob>(pCompiledShaderCode);

	return 0;
}

INT Material::InitPixelShader(ID3D11Device* pD3DDevice, Shader shader)
{
	ID3DBlob* pCompiledShaderCode = nullptr;
	HRESULT hr = {};

	hr = D3DReadFileToBlob(pixelShaders[shader], &pCompiledShaderCode);
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

INT Material::InitMatrixBuffer(ID3D11Device* pD3DDevice)
{
	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = sizeof(MatrixBuffer);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HRESULT hr = pD3DDevice->CreateBuffer(&desc, nullptr, &pVSMatrixBuffer);
	if (FAILED(hr)) return 51;

	return 0;
}

INT Material::InitMaterialBuffer(ID3D11Device* pD3DDevice, MaterialLoaderData* pMaterialData)
{
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.ByteWidth = sizeof(MaterialData);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;

	MaterialData* pMaterial = new MaterialData;
	pMaterial->specularPower = pMaterialData->specularPower;
	pMaterial->dissolve = pMaterialData->dissolve;

	D3D11_SUBRESOURCE_DATA subResourceData = {};
	subResourceData.pSysMem = pMaterial;

	HRESULT hr = pD3DDevice->CreateBuffer(&bufferDesc, &subResourceData, &pPSMaterialBuffer);
	if (FAILED(hr)) 
		return 30;

	return 0;
}

INT Material::InitTextureAndSamplerState(ID3D11Device* pD3DDevice, std::string materialName)
{
	if (materialName == "")
		materialName = "Default.mtl";
		
	MaterialLoaderData* pMaterialData = MaterialLoader::LoadFromFile(materialName);
	InitMaterialBuffer(pD3DDevice, pMaterialData);

	HRESULT hr = CreateWICTextureFromFile(pD3DDevice, pMaterialData->textureFileName.c_str(), nullptr, &pTexture);
	if (FAILED(hr)) return 53;

	if(pMaterialData->normalMapFileName != L"")
		hr = CreateWICTextureFromFile(pD3DDevice, pMaterialData->normalMapFileName.c_str(), nullptr, &pNormalMap);
	if (FAILED(hr)) return 53;

	D3D11_SAMPLER_DESC desc = {};
	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;

	hr = pD3DDevice->CreateSamplerState(&desc, &pSamplerState);
	if (FAILED(hr)) return 55;

	pMaterialData = nullptr;

	return 0;
}

INT Material::InitAdditionalBuffers(ID3D11Device* pD3DDevice)
{
	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = sizeof(AdditionalData);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HRESULT hr = pD3DDevice->CreateBuffer(&desc, nullptr, &pVSAdditionalBuffer);
	hr = pD3DDevice->CreateBuffer(&desc, nullptr, &pPSAdditionalBuffer);
	if (FAILED(hr)) return 53;
	return 0;
}

void Material::SetMatrixBuffer(ID3D11DeviceContext* pD3DDeviceContext, const XMMATRIX& rTransformationMatrix, const XMMATRIX& rViewProjectionMatrix)
{
	XMMATRIX worldViewProjectionMatrix = XMMatrixTranspose(rTransformationMatrix * rViewProjectionMatrix);

	D3D11_MAPPED_SUBRESOURCE data = {};
	HRESULT hr = pD3DDeviceContext->Map(pVSMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
	if (FAILED(hr)) return;

	MatrixBuffer* matrixBuffer = static_cast<MatrixBuffer*>(data.pData);

	XMStoreFloat4x4(&matrixBuffer->worldViewProjectionMatrix, worldViewProjectionMatrix);
	XMStoreFloat4x4(&matrixBuffer->worldMatrix, XMMatrixTranspose(rTransformationMatrix));

	pD3DDeviceContext->Unmap(pVSMatrixBuffer, 0);

	pD3DDeviceContext->VSSetConstantBuffers(0, 1, &pVSMatrixBuffer);
}

void Material::SetAdditionalBuffers(ID3D11DeviceContext* pD3DDeviceContext)
{
	D3D11_MAPPED_SUBRESOURCE data = {};
	HRESULT hr = pD3DDeviceContext->Map(pVSAdditionalBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
	if (FAILED(hr)) return;
	AdditionalData* additionalData = static_cast<AdditionalData*>(data.pData);
	additionalData = pVSData;
	pD3DDeviceContext->Unmap(pVSAdditionalBuffer, 0);

	data = {};
	hr = pD3DDeviceContext->Map(pPSAdditionalBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
	if (FAILED(hr)) return;
	AdditionalData* additionalData = static_cast<AdditionalData*>(data.pData);
	additionalData = pPSData;
	pD3DDeviceContext->Unmap(pPSAdditionalBuffer, 0);

	pD3DDeviceContext->VSSetConstantBuffers(2, 1, &pVSAdditionalBuffer);
	pD3DDeviceContext->PSSetConstantBuffers(2, 1, &pVSAdditionalBuffer);
}
