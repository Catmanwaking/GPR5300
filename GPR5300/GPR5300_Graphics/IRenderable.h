#pragma once
class IRenderable
{
public:
	virtual void Render(ID3D11DeviceContext* pD3DDeviceContext, const XMMATRIX& viewProjectionMatrix) {};
};