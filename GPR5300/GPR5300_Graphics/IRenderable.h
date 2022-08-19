#pragma once
//Renderable interface.
//All IRenderables will be added to the render queue upon creation
class IRenderable
{
public:
	//Executes the Render action of the Object
	virtual void Render(ID3D11DeviceContext* pD3DDeviceContext, const XMMATRIX& viewProjectionMatrix) {};
};