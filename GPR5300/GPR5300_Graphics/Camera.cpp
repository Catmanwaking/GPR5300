#include "Camera.h"

using namespace DirectX;

INT Camera::Init(ID3D11Device* pD3DDevice, UINT screenWidth, UINT screenHeight, std::string skyBoxName)
{
    projectionMatrix = XMMatrixPerspectiveFovLH
    (
        XM_PIDIV2,
        static_cast<float>(screenWidth) / static_cast<float>(screenHeight),
        0.1f,
        1000.0f
    );

    skyBox.Init(pD3DDevice, skyBoxName);

    return 0;
}

void Camera::Render(ID3D11DeviceContext* pD3DDeviceContext)
{
    XMVECTOR forward = pTransform->Forward().ToXMVector();
    XMVECTOR up = pTransform->Up().ToXMVector();

    viewMatrix = XMMatrixLookToLH(XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f), forward, up);
    skyBox.Render(pD3DDeviceContext, viewMatrix * projectionMatrix);

    viewMatrix = XMMatrixLookToLH(pTransform->GetPosition().ToXMVector(),forward,up);
    viewProjectionMatrix = viewMatrix * projectionMatrix;
}

void Camera::DeInit()
{
    //TODO cleanup matrices
}
