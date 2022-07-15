#include "Light.h"
#include "Utils.h"

INT Light::Init(D3DLIGHT9& light, DWORD id)
{
    this->light = light;
    this->id = id;
    return 0;
}

void Light::Render(IDirect3DDevice9* pD3DDevice)
{
    pD3DDevice->SetLight(id, &light);
    pD3DDevice->LightEnable(id, TRUE);
}

void Light::DeInit()
{
}
