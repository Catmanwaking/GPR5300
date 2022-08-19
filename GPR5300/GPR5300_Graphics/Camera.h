#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "GameObject.h"
#include "IRenderable.h"
#include "SkyBox.h"
#include "Mesh.h"
#include "Shaders.h"

using namespace DirectX;
using namespace Shaders;

struct CameraData
{
	XMFLOAT3 cameraPosition;
	FLOAT padding;
};

class Camera : public Component, public IRenderable
{
public:
	//Initializes the Camera component.
	INT Init(ID3D11Device* pD3DDevice, ID3D11DepthStencilView* pDepthStencilView, UINT screenWidth, UINT screenHeight);
	//Initializes the Camera buffer.
	INT InitCameraBuffer(ID3D11Device* pD3DDevice);
	//Renders the SkyBox and calculates the ViewProjectionMatrix.
	virtual void Render(ID3D11DeviceContext* pD3DDeviceContext);
	virtual void DeInit();

	//Returns the ViewProjectionMatrix.
	const XMMATRIX& GetViewProjectionMatrix() const { return viewProjectionMatrix; }

private:
	SkyBox skyBox = {};

	XMMATRIX viewMatrix = {};
	XMMATRIX projectionMatrix = {};
	XMMATRIX viewProjectionMatrix = {}; //since (AB)C = A(BC)
	ID3D11Buffer* pCameraBuffer = nullptr;

	ID3D11DepthStencilView* pDepthStencilView = nullptr;

	//Sets the Camera buffer.
	void SetCameraBuffer(ID3D11DeviceContext* pD3DDeviceContext);
};

