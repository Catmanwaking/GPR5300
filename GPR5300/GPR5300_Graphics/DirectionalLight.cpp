#include "DirectionalLight.h"

INT DirectionalLight::Init(DirLightData lightData)
{
    data = lightData;
    return 0;
}

void DirectionalLight::Update()
{
    data.direction = pTransform->Forward().ToXMFloat3();
}

void DirectionalLight::DeInit()
{
}
