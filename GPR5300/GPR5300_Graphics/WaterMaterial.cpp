#include "WaterMaterial.h"
#include "Time.h"

void WaterMaterial::Render(ID3D11DeviceContext* pD3DDeviceContext, const XMMATRIX& rTransformationMatrix, const XMMATRIX& rViewProjectionMatrix)
{
	pD3DDeviceContext->VSSetShader(pVertexShader, nullptr, 0);
	pD3DDeviceContext->PSSetShader(pPixelShader, nullptr, 0);

	SetMatrixBuffer(pD3DDeviceContext, rTransformationMatrix, rViewProjectionMatrix);
	pD3DDeviceContext->PSSetConstantBuffers(1, 1, &pMaterialBuffer);
	pD3DDeviceContext->PSSetShaderResources(0, 1, &pNormalMap);

	pD3DDeviceContext->PSSetSamplers(0, 1, &pSamplerState);
}

void WaterMaterial::DeInit()
{
}

INT WaterMaterial::InitAdditionalBuffers(ID3D11Device* pD3DDevice)
{
	D3D11_BUFFER_DESC desc1 = {};
	desc1.ByteWidth = sizeof(TilingOffsetData);
	desc1.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc1.Usage = D3D11_USAGE_DYNAMIC;
	desc1.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HRESULT hr1 = pD3DDevice->CreateBuffer(&desc1, nullptr, &pTilingOffsetBuffer);
	if (FAILED(hr1)) 
		return 53;

	D3D11_BUFFER_DESC desc2 = {};
	desc2.ByteWidth = sizeof(WaterData);
	desc2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc2.Usage = D3D11_USAGE_DEFAULT;

	WaterData* data = new WaterData;
	data->mainColor = { 0.0f, 0.0f, 1.0f, 1.0f }; //TODO deep blue
	data->sideColor = { 0.0f, 0.0f, 1.0f, 1.0f };
	data->fresnelMult = 1.0f;
	data->fresnelPower = 1.0f;

	D3D11_SUBRESOURCE_DATA subResourceData = {};
	subResourceData.pSysMem = data;

	HRESULT hr2 = pD3DDevice->CreateBuffer(&desc2, &subResourceData, &pWaterBuffer);
	if (FAILED(hr2)) 
		return 53;

	return 0;
}

void WaterMaterial::SetAdditionalBuffers(ID3D11DeviceContext* pD3DDeviceContext)
{
	FLOAT deltaTime = Time::GetInstance()->GetDeltaTime();

	D3D11_MAPPED_SUBRESOURCE data = {};
	HRESULT hr = pD3DDeviceContext->Map(pTilingOffsetBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
	if (FAILED(hr)) return;

	TilingOffsetData* tilingOffsetBuffer = static_cast<TilingOffsetData*>(data.pData);

	tilingOffsetBuffer->offset.x = deltaTime * 1.0f; //wavespeed
	tilingOffsetBuffer->offset.y = deltaTime * 2.0f; //cascadespeedmult
	tilingOffsetBuffer->tiling = { 1.0f, 1.0f };

	pD3DDeviceContext->Unmap(pTilingOffsetBuffer, 0);

	pD3DDeviceContext->VSSetConstantBuffers(2, 1, &pTilingOffsetBuffer);
	pD3DDeviceContext->PSSetConstantBuffers(2, 1, &pWaterBuffer);
}
