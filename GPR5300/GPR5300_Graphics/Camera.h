#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "GameObject.h"
#include "IUpdateable.h"

using namespace DirectX;

class Camera : public Component, public IUpdateable
{
public:
	INT Init(UINT screenWidth, UINT screenHeight);
	virtual void Update();
	virtual void DeInit();
	//const XMMATRIX& GetViewMatrix() const { return viewMatrix; }
	//const XMMATRIX& GetProjectionMatrix() const { return projectionMatrix; }

	const XMMATRIX& GetViewProjectionMatrix() const { return viewProjectionMatrix; }

private:
	XMMATRIX viewMatrix = {};
	XMMATRIX projectionMatrix = {};
	XMMATRIX viewProjectionMatrix = {}; //since (AB)C = A(BC)
};

