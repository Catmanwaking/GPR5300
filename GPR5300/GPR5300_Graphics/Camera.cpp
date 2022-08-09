#include "Camera.h"

using namespace DirectX;

INT Camera::Init(ID3D11Device* pD3DDevice, ID3D11DepthStencilView* pDepthStencilView, UINT screenWidth, UINT screenHeight, std::string skyBoxName, Shader shader)
{
    INT error = 0;
    InitCameraBuffer(pD3DDevice);

    projectionMatrix = XMMatrixPerspectiveFovLH
    (
        XM_PIDIV2,
        static_cast<float>(screenWidth) / static_cast<float>(screenHeight),
        0.1f,
        1000.0f
    );

    this->pDepthStencilView = pDepthStencilView;

    skyBox.Init(pD3DDevice, skyBoxName, shader);

    return 0;
}

INT Camera::InitCameraBuffer(ID3D11Device* pD3DDevice)
{
    D3D11_BUFFER_DESC desc = {};
    desc.ByteWidth = sizeof(CameraData);
    desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    HRESULT hr = pD3DDevice->CreateBuffer(&desc, nullptr, &pCameraBuffer);
    if (FAILED(hr)) return 51;

    return 0;
}

void Camera::Render(ID3D11DeviceContext* pD3DDeviceContext)
{
    XMVECTOR forward = pTransform->Forward().ToXMVector();
    XMVECTOR up = pTransform->Up().ToXMVector();

    //render skybox and clear depth buffer
    viewMatrix = XMMatrixLookToLH(XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f), forward, up);
    skyBox.Render(pD3DDeviceContext, viewMatrix * projectionMatrix);
    pD3DDeviceContext->ClearDepthStencilView(pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0xffffffff);

    viewMatrix = XMMatrixLookToLH(pTransform->GetPosition().ToXMVector(),forward,up);
    viewProjectionMatrix = viewMatrix * projectionMatrix;

    SetCameraBuffer(pD3DDeviceContext);
}

void Camera::DeInit()
{
    //TODO cleanup
}

void Camera::SetCameraBuffer(ID3D11DeviceContext* pD3DDeviceContext)
{
    D3D11_MAPPED_SUBRESOURCE data = {};
    HRESULT hr = pD3DDeviceContext->Map(pCameraBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
    if (FAILED(hr)) return;

    CameraData* cameraBuffer = static_cast<CameraData*>(data.pData);

    cameraBuffer->cameraPosition = pTransform->GetPosition().ToXMFloat3();

    pD3DDeviceContext->Unmap(pCameraBuffer, 0);

    pD3DDeviceContext->VSSetConstantBuffers(1, 1, &pCameraBuffer);
}
