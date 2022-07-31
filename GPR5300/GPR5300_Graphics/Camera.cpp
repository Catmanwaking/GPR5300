#include "Camera.h"

using namespace DirectX;

INT Camera::Init(UINT screenWidth, UINT screenHeight)
{
    projectionMatrix = XMMatrixPerspectiveFovLH
    (
        XM_PIDIV2,
        static_cast<float>(screenWidth) / static_cast<float>(screenHeight),
        0.1f,
        1000.0f
    );

    return 0;
}

void Camera::Update()
{
    viewMatrix = XMMatrixLookToLH
    (
        pTransform->GetPosition().ToXMVector(),
        pTransform->Forward().ToXMVector(),
        pTransform->Up().ToXMVector()
    );
    viewProjectionMatrix = viewMatrix * projectionMatrix;
}

void Camera::DeInit()
{
    //TODO cleanup matrices
}
