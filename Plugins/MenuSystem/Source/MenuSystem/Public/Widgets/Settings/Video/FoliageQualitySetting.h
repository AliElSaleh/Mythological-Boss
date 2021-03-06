// Copyright Ali El Saleh 2019

#pragma once

#include "Widgets/Settings/GraphicsSetting.h"
#include "FoliageQualitySetting.generated.h"

/**
 * Manages the foliage quality in the game
 */
UCLASS()
class MENUSYSTEM_API UFoliageQualitySetting final : public UGraphicsSetting
{
	GENERATED_BODY()
	
public:
	void Apply() override;
};
