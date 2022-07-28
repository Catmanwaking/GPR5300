#pragma once
#include "Camera.h"

INT Camera::Init(UINT screenWidth, UINT screenHeight)
{
    XMMATRIX lookMatrix = XMMatrixLookToLH
    (
        XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f),
        XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f),
        XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)
    );
    XMStoreFloat4x4(&viewMatrix, lookMatrix);

    XMMATRIX perspectiveMatrix = XMMatrixPerspectiveFovLH
    (
        XM_PIDIV2,
        static_cast<float>(screenWidth) / static_cast<float>(screenHeight),
        0.3f,
        1000.0f
    );
    XMStoreFloat4x4(&projectionMatrix, perspectiveMatrix);

    return 0;
}

void Camera::Update()
{
}

void Camera::DeInit()
{
}
