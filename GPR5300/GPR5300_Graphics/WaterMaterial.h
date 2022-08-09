#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <string>
#include "Material.h"
#include "Shaders.h"

using namespace DirectX;
using namespace Shaders;

struct CameraBuffer
{
	XMFLOAT3 cameraPosition;
	FLOAT padding;
};

class WaterMaterial : public Material
{
public:
	virtual void Render(ID3D11DeviceContext* pD3DDeviceContext, const XMMATRIX& rTransformationMatrix, const XMMATRIX& rViewProjectionMatrix);
	virtual void DeInit();

protected:
	virtual void SetMatrixBuffer(ID3D11DeviceContext* pD3DDeviceContext, const XMMATRIX& rTransformationMatrix, const XMMATRIX& rViewProjectionMatrix);
};

