#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <string>
#include "Material.h"
#include "Shaders.h"

using namespace DirectX;
using namespace Shaders;

struct TilingOffsetData
{
	XMFLOAT2 tiling;
	XMFLOAT2 offset;
};

struct WaterData
{
	XMFLOAT4 mainColor;
	XMFLOAT4 sideColor;
    float fresnelPower;
    float fresnelMult;
	XMFLOAT2 padding;
};

class WaterMaterial : public Material
{
public:
	virtual void Render(ID3D11DeviceContext* pD3DDeviceContext, const XMMATRIX& rTransformationMatrix, const XMMATRIX& rViewProjectionMatrix);
	virtual void DeInit();

protected:
	INT InitAdditionalBuffers(ID3D11Device* pD3DDevice) override;
	virtual void SetAdditionalBuffers(ID3D11DeviceContext* pD3DDeviceContext);

	ID3D11Buffer* pTilingOffsetBuffer = nullptr;
	ID3D11Buffer* pWaterBuffer = nullptr;
};

