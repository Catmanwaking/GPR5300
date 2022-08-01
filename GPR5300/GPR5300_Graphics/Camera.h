#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "GameObject.h"
#include "IRenderable.h"
#include "SkyBox.h"

using namespace DirectX;

class Camera : public Component, public IRenderable
{
public:
	INT Init(ID3D11Device* pD3DDevice, UINT screenWidth, UINT screenHeight, std::string skyBoxName);
	virtual void Render(ID3D11DeviceContext* pD3DDeviceContext);
	virtual void DeInit();
	//const XMMATRIX& GetViewMatrix() const { return viewMatrix; }
	//const XMMATRIX& GetProjectionMatrix() const { return projectionMatrix; }

	const XMMATRIX& GetViewProjectionMatrix() const { return viewProjectionMatrix; }

private:
	SkyBox skyBox = {};

	XMMATRIX viewMatrix = {};
	XMMATRIX projectionMatrix = {};
	XMMATRIX viewProjectionMatrix = {}; //since (AB)C = A(BC)
};

