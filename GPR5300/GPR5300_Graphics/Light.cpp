#include "Light.h"
#include "Utils.h"

INT Light::Init(ID3D11Device* pD3DDevice, LightData& light, UINT id)
{
    this->light = light;
    this->id = id;

    D3D11_BUFFER_DESC desc = {};
    desc.ByteWidth = sizeof(LightData);
    desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    desc.Usage = D3D11_USAGE_IMMUTABLE;

    D3D11_SUBRESOURCE_DATA data = {};
    data.pSysMem = &light;

    HRESULT hr = pD3DDevice->CreateBuffer(&desc, &data, &pLightBuffer);
    if (FAILED(hr)) return 70;

    return 0;
}

void Light::Render(ID3D11DeviceContext* pD3DDeviceContext)
{
    pD3DDeviceContext->PSSetConstantBuffers(id, 1, &pLightBuffer);
}

void Light::DeInit()
{
    SafeRelease<ID3D11Buffer>(pLightBuffer);
}