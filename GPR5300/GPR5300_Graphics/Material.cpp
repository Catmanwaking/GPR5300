#include "Material.h"
#include "WICTextureLoader9.h"
#include "Utils.h"
#include "MaterialData.h"
#include "MaterialLoader.h"

using namespace DirectX;

INT Material::Init(IDirect3DDevice9* pD3DDevice, std::string materialName)
{
	MaterialData* pMaterialData = MaterialLoader::LoadFromFile(materialName);

	HRESULT hr = CreateWICTextureFromFile(pD3DDevice, pMaterialData->textureFileName.c_str(),&pTexture, 0, WIC_LOADER_MIP_AUTOGEN);
	if (FAILED(hr)) return 50;
	material.Ambient = pMaterialData->ambient;
	material.Diffuse = pMaterialData->diffuse;
	material.Specular = pMaterialData->specular;
	material.Power = pMaterialData->specularPower;
	material.Emissive = pMaterialData->emissive;

	pMaterialData = nullptr;

	return 0;
}

void Material::Render(IDirect3DDevice9* pD3DDevice)
{
	if (pTexture == nullptr) return;

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