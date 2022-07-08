#include <DirectXMath.h>
#include "Camera.h"

using namespace DirectX;

INT Camera::Init(IDirect3DDevice9* pD3DDevice, UINT screenWidth, UINT screenHeight)
{
    XMMATRIX lookMatrix = XMMatrixLookToLH
    (
        XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f),
        XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f),
        XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)
    );
    XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(&viewMatrix), lookMatrix);
    pD3DDevice->SetTransform(D3DTS_VIEW, &viewMatrix);

    XMMATRIX perspectiveMatrix = XMMatrixPerspectiveFovLH
    (
        XM_PIDIV2,
        static_cast<float>(screenWidth) / static_cast<float>(screenHeight),
        0.3f,
        1000.0f
    );
    XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(&projectionMatrix), perspectiveMatrix);
    pD3DDevice->SetTransform(D3DTS_PROJECTION, &projectionMatrix);

    return 0;
}

void Camera::Update()
{
}

void Camera::DeInit()
{
}
