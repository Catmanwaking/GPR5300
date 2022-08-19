#include "AdditionalDataFiller.h"

INT AdditionalDataFiller::Init()
{
    return 0;
}

void AdditionalDataFiller::Update()
{
}

void AdditionalDataFiller::DeInit()
{
}

void AdditionalDataFiller::SetMaterial(Material* pMaterial)
{
    pVSData = pMaterial->GetVSData();
    pPSData = pMaterial->GetPSData();
}
