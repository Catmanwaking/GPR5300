#include <DirectXMath.h>
#include "Camera.h"

using namespace DirectX;

INT Camera::Init(IDirect3DDevice9* pD3DDevice, UINT screenWidth, UINT screenHeight)
{
    this->pD3DDevice = pD3DDevice;

    XMMATRIX perspectiveMatrix = XMMatrixPerspectiveFovLH
    (
        XM_PIDIV2,
        static_cast<float>(screenWidth) / static_cast<float>(screenHeight),
        0.1f,
        1000.0f
    );
    XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(&projectionMatrix), perspectiveMatrix);
    pD3DDevice->SetTransform(D3DTS_PROJECTION, &projectionMatrix);

    return 0;
}

void Camera::Update()
{
    XMMATRIX lookMatrix = XMMatrixLookToLH
    (
        pTransform->GetPosition().ToXMVector(),
        pTransform->Forward().ToXMVector(),
        pTransform->Up().ToXMVector()
    );
    XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(&viewMatrix), lookMatrix);
    pD3DDevice->SetTransform(D3DTS_VIEW, &viewMatrix);
}

void Camera::DeInit()
{
}
