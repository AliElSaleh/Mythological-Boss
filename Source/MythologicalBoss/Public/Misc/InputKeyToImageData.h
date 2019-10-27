// Copyright Overthrone Studios 2019

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/Texture2D.h"
#include "InputKeyToImageData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class MYTHOLOGICALBOSS_API UInputKeyToImageData final : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditInstanceOnly, Category = "Keys to Textures")
		TMap<FKey, UTexture2D*> InputKeys;

	UFUNCTION(BlueprintCallable, Category = "Keys to Textures")
		UTexture2D* GetTextureFromKey(FKey Key);
};
