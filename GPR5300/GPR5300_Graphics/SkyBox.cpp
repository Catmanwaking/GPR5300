#include <d3dcompiler.h>
#include <xutility>
#include "WICTextureLoader11.h"
#include "SkyBox.h"
#include "Utils.h"
#include "MaterialData.h"
#include "MaterialLoader.h"
#include "MeshLoader.h"

#pragma comment(lib, "d3dcompiler.lib")

INT SkyBox::Init(ID3D11Device* pD3DDevice, std::string skyBoxName)
{
	pMeshData = MeshLoader::LoadFromFile(skyBoxName);

	INT error = InitVertexBuffer(pD3DDevice);
	if (error) return error;

	error = InitIndexBuffer(pD3DDevice);
	if (error) return error;

	error = InitVertexShader(pD3DDevice);
	if (error) return error;

	error = InitPixelShader(pD3DDevice);
	if (error) return error;

	error = InitMatrixBuffer(pD3DDevice);
	if (error) return error;

	error = InitTextureAndSamplerState(pD3DDevice, pMeshData->materialFileName);
	if (error) return error;

	pMeshData->DeInit();
	pMeshData = nullptr;

    return 0;
}

void SkyBox::Render(ID3D11DeviceContext* pD3DDeviceContext, const XMMATRIX& rViewProjectionMatrix)
{
	if (pTexture == nullptr) return;

	pD3DDeviceContext->IASetInputLayout(pInputLayout);
	pD3DDeviceContext->VSSetShader(pVertexShader, nullptr, 0);
	pD3DDeviceContext->PSSetShader(pPixelShader, nullptr, 0);

	SetMatrixBuffer(pD3DDeviceContext, rViewProjectionMatrix);
	pD3DDeviceContext->PSSetShaderResources(0, 1, &pTexture);
	pD3DDeviceContext->PSSetSamplers(0, 1, &pSamplerState);

	static UINT offset = 0;
	pD3DDeviceContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &vertexStride, &offset);
	pD3DDeviceContext->IASetIndexBuffer(pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	pD3DDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pD3DDeviceContext->DrawIndexed(indexCount, 0, 0);
}

void SkyBox::DeInit()
{
	SafeRelease<ID3D11SamplerState>(pSamplerState);
	SafeRelease<ID3D11ShaderResourceView>(pTexture);
	SafeRelease<ID3D11Buffer>(pMatrixBuffer);
	SafeRelease<ID3D11InputLayout>(pInputLayout);
	SafeRelease<ID3D11PixelShader>(pPixelShader);
	SafeRelease<ID3D11VertexShader>(pVertexShader);

	SafeRelease<ID3D11Buffer>(pVertexBuffer);
	SafeRelease<ID3D11Buffer>(pIndexBuffer);
}

INT SkyBox::InitVertexBuffer(ID3D11Device* pD3DDevice)
{
	vertexCount = pMeshData->vertexCount;
	vertexStride = sizeof(Vertex);

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.ByteWidth = vertexCount * vertexStride;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;

	D3D11_SUBRESOURCE_DATA subResourceData = {};
	subResourceData.pSysMem = pMeshData->vertices->data();

	HRESULT hr = pD3DDevice->CreateBuffer(&bufferDesc, &subResourceData, &pVertexBuffer);
	if (FAILED(hr)) return 30;

	return 0;
}

INT SkyBox::InitIndexBuffer(ID3D11Device* pD3DDevice)
{
	indexCount = pMeshData->indexCount;

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.ByteWidth = indexCount * sizeof(USHORT);
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;

	D3D11_SUBRESOURCE_DATA subResourceData = {};
	subResourceData.pSysMem = pMeshData->indices->data();

	HRESULT hr = pD3DDevice->CreateBuffer(&bufferDesc, &subResourceData, &pIndexBuffer);
	if (FAILED(hr)) return 32;

	return 0;
}

INT SkyBox::InitVertexShader(ID3D11Device* pD3DDevice)
{
	ID3DBlob* pCompiledShaderCode = nullptr;
	HRESULT hr = {};

	hr = D3DReadFileToBlob(TEXT("SkyBoxVertexShader.cso"), &pCompiledShaderCode);
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
	if (error) return error;

	SafeRelease<ID3DBlob>(pCompiledShaderCode);

	return 0;
}

INT SkyBox::InitPixelShader(ID3D11Device* pD3DDevice)
{
	ID3DBlob* pCompiledShaderCode = nullptr;
	HRESULT hr = {};

	hr = D3DReadFileToBlob(TEXT("SkyBoxPixelShader.cso"), &pCompiledShaderCode);
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

INT SkyBox::InitInputLayot(ID3D11Device* pD3DDevice, ID3DBlob* pCompiledShaderCode)
{
	D3D11_INPUT_ELEMENT_DESC elementDescription[4] = {}; //TODO INPUT LAYOUT DOESN'T CHANGE -> unify

	elementDescription[0].SemanticName = "POSITION";
	elementDescription[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;

	elementDescription[1].SemanticName = "NORMAL";
	elementDescription[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	elementDescription[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	elementDescription[2].SemanticName = "TEXCOORD";
	elementDescription[2].Format = DXGI_FORMAT_R32G32_FLOAT;
	elementDescription[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	elementDescription[3].SemanticName = "COLOR";
	elementDescription[3].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	elementDescription[3].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

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

INT SkyBox::InitMatrixBuffer(ID3D11Device* pD3DDevice)
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

INT SkyBox::InitTextureAndSamplerState(ID3D11Device* pD3DDevice, std::string materialName)
{
	MaterialData* pMaterialData = MaterialLoader::LoadFromFile(materialName);

	HRESULT hr = CreateWICTextureFromFile(pD3DDevice, pMaterialData->textureFileName.c_str(), nullptr, &pTexture);
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

void SkyBox::SetMatrixBuffer(ID3D11DeviceContext* pD3DDeviceContext, const XMMATRIX& rViewProjectionMatrix)
{
	D3D11_MAPPED_SUBRESOURCE data = {};
	HRESULT hr = pD3DDeviceContext->Map(pMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
	if (FAILED(hr)) return;

	MatrixBuffer* matrixBuffer = static_cast<MatrixBuffer*>(data.pData);

	XMStoreFloat4x4(&matrixBuffer->viewProjectionMatrix, XMMatrixTranspose(rViewProjectionMatrix));

	pD3DDeviceContext->Unmap(pMatrixBuffer, 0);

	pD3DDeviceContext->VSSetConstantBuffers(0, 1, &pMatrixBuffer);
}
