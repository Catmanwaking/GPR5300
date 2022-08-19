#include "SkyBoxMaterial.h"

void SkyBoxMaterial::Render(ID3D11DeviceContext* pD3DDeviceContext, const XMMATRIX& rViewProjectionMatrix)
{
	if (pTexture == nullptr) return;

	SwapSkyBox();

	pD3DDeviceContext->VSSetShader(pVertexShader, nullptr, 0);
	pD3DDeviceContext->PSSetShader(pPixelShader, nullptr, 0);

	SetMatrixBuffer(pD3DDeviceContext, rViewProjectionMatrix);
	pD3DDeviceContext->PSSetConstantBuffers(0, 1, &pPSMaterialBuffer);
	pD3DDeviceContext->PSSetShaderResources(0, 1, &pTexture);
	pD3DDeviceContext->PSSetSamplers(0, 1, &pSamplerState);
}

void SkyBoxMaterial::DeInit()
{
}

void SkyBoxMaterial::SetMatrixBuffer(ID3D11DeviceContext* pD3DDeviceContext, const XMMATRIX& rViewProjectionMatrix)
{
	XMMATRIX viewProjectionMatrix = XMMatrixTranspose(rViewProjectionMatrix);

	D3D11_MAPPED_SUBRESOURCE data = {};
	HRESULT hr = pD3DDeviceContext->Map(pVSMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
	if (FAILED(hr)) return;

	MatrixBuffer* matrixBuffer = static_cast<MatrixBuffer*>(data.pData);

	XMStoreFloat4x4(&matrixBuffer->worldViewProjectionMatrix, viewProjectionMatrix);

	pD3DDeviceContext->Unmap(pVSMatrixBuffer, 0);

	pD3DDeviceContext->VSSetConstantBuffers(0, 1, &pVSMatrixBuffer);
}

void SkyBoxMaterial::SwapSkyBox()
{
	static bool keyDown = false;
	SHORT keyState = GetAsyncKeyState('P');
	if (keyState & 0x8000)
	{
		if (!keyDown)
		{
			auto foo = pTexture;
			pTexture = pNormalMap;
			pNormalMap = foo;
		}
		keyDown = true;
	}
	else
		keyDown = false;
}
