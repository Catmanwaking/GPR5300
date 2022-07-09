#pragma once
class IRenderable
{
public:
	virtual void Render(IDirect3DDevice9* pD3DDevice) {};
};