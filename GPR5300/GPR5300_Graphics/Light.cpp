#include "Light.h"
#include "Utils.h"

INT Light::Init(ID3D11Device* pD3DDevice)
{
    D3D11_BUFFER_DESC desc = {};
    desc.ByteWidth = sizeof(LightData);
    desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    HRESULT hr = pD3DDevice->CreateBuffer(&desc, nullptr, &pLightBuffer);
    if (FAILED(hr)) return 70;

    ambientLight = { 0.3f, 0.3f, 0.3f, 1.0f };

    return 0;
}

void Light::Render(ID3D11DeviceContext* pD3DDeviceContext)
{
    D3D11_MAPPED_SUBRESOURCE data = {};
    HRESULT hr = pD3DDeviceContext->Map(pLightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
    if (FAILED(hr)) return;

    LightData* lightBuffer = static_cast<LightData*>(data.pData);

    lightBuffer->dirLightBuffer = pDirLight->GetData();
    for (UINT i = 0; i < pointLightCount; i++)
    {
        lightBuffer->pointLight[i] = pPointLights[i]->GetData();
    }
    lightBuffer->ambientLight = ambientLight;
    lightBuffer->pointLightCount = pointLightCount;

    pD3DDeviceContext->Unmap(pLightBuffer, 0);

    pD3DDeviceContext->PSSetConstantBuffers(0, 1, &pLightBuffer);
}

void Light::DeInit()
{
    SafeRelease<ID3D11Buffer>(pLightBuffer);
}

void Light::AddLight(DirectionalLight* pDirLight)
{
    this->pDirLight = pDirLight;
}

void Light::AddLight(PointLight* pPointLight)
{
    if (pointLightCount >= 8) return;
    this->pPointLights[pointLightCount] = pPointLight;
    pointLightCount++;
}
