#include "Material.h"
#include "WICTextureLoader9.h"
#include "Utils.h"

using namespace DirectX;

INT Material::Init(IDirect3DDevice9* pD3DDevice, LPCTSTR texturePath)
{
	HRESULT hr = CreateWICTextureFromFile(pD3DDevice, texturePath, &pTexture, 0, WIC_LOADER_MIP_AUTOGEN);
	if (FAILED(hr))
		return 50;

	material.Ambient = { 1.0f, 1.0f, 1.0f, 1.0f };
	material.Diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	material.Specular = { 1.0f, 1.0f, 1.0f, 1.0f };
	material.Power = 1024.0f;
	//material.Emissive = { 1.0f, 0.0f, 0.0f, 1.0f };

	return 0;
}

void Material::Render(IDirect3DDevice9* pD3DDevice)
{
	pD3DDevice->SetTexture(0, pTexture);
	pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	pD3DDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, D3DCOLOR_XRGB(255, 0, 255));
	pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	pD3DDevice->SetSamplerState(0, D3DSAMP_MAXMIPLEVEL, 0);
	pD3DDevice->SetSamplerState(0, D3DSAMP_MIPMAPLODBIAS, 0);
	pD3DDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 1);

	pD3DDevice->SetMaterial(&material);
}

void Material::DeInit()
{
	SafeRelease<IDirect3DTexture9>(pTexture);
}
