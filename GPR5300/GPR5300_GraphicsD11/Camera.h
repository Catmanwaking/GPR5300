#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

class Camera
{
public:
	INT Init(UINT screenWidth, UINT screenHeight);
	void Update();
	void DeInit();
	const XMFLOAT4X4& GetViewMatrix() const { return viewMatrix; }
	const XMFLOAT4X4& GetProjectionMatrix() const { return projectionMatrix; }

private:
	XMFLOAT4X4 viewMatrix = {};
	XMFLOAT4X4 projectionMatrix = {};
};

