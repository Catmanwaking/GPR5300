#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <string>
#include "MeshLoaderData.h"
#include "Mesh.h"
#include "SkyBoxMaterial.h"

using namespace DirectX;

class SkyBox : public Mesh
{
public:
	//Initializes the SkyBox
	virtual INT Init(ID3D11Device* pD3DDevice);
	//Renders the SkyBox
	virtual void Render(ID3D11DeviceContext* pD3DDeviceContext, const XMMATRIX& viewProjectionMatrix);
	virtual void DeInit();

private:
	SkyBoxMaterial material;
};

