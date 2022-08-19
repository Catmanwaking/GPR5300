#pragma once
#include <d3d11.h>
#include "Component.h"
#include "IUpdateable.h"
#include "Material.h"

class AdditionalDataFiller : public Component, public IUpdateable
{
public:
	INT Init();
	virtual void Update();
	virtual void DeInit();

	void SetMaterial(Material* pMaterial);

protected:
	AdditionalData* pVSData = nullptr;
	AdditionalData* pPSData = nullptr;
};

