#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <string>
#include "Material.h"
#include "Shaders.h"

using namespace DirectX;
using namespace Shaders;

class SkyBoxMaterial : public Material
{
public:
	//Renders the SkyBox.
	virtual void Render(ID3D11DeviceContext* pD3DDeviceContext, const XMMATRIX& rViewProjectionMatrix);
	virtual void DeInit();

protected:
	//Sets the Matrixbuffer needed to render the SkyBox.
	virtual void SetMatrixBuffer(ID3D11DeviceContext* pD3DDeviceContext, const XMMATRIX& rViewProjectionMatrix);

private:
	//Swaps the SkyBox texture by pressing 'P' to make the headinstructor happy.
	void SwapSkyBox();
};

