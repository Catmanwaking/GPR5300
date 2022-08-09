#include "PointLight.h"

INT PointLight::Init(PointLightData lightData)
{
    data = lightData;
    return 0;
}

void PointLight::Update()
{
    data.position = pTransform->GetPosition().ToXMFloat3();
}

void PointLight::DeInit()
{
}
