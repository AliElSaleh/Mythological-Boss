// Copyright Ali El Saleh 2019

#pragma once

#include "Settings/MenuSetting.h"
#include "VideoSetting.generated.h"

/**
 * Base class for any type of video setting
 */
UCLASS()
class MENUSYSTEM_API UVideoSetting : public UMenuSetting
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Video Setting")
		FString SelectedOption;

	FString DefaultOption;
	FString PreviousSelectedOption;

	UPROPERTY(EditInstanceOnly, Category = "Video Setting")
		TArray<FString> Options;

	class UComboBoxString* DropDownList;
	class USlider* Slider;
};
