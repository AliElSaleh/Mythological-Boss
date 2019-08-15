// Copyright Overthrone Studios 2019

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FootstepData.h"
#include "FootstepCollection.generated.h"

/**
 * Contains an array of Footstep Data assets
 */
UCLASS()
class MYTHOLOGICALBOSS_API UFootstepCollection final : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
		TArray<UFootstepData*> GetFootstepMappings() const { return FootstepMappings; }

	UPROPERTY(EditInstanceOnly, Category = "Footsteps")
		uint8 bDebug : 1;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Footsteps")
		TArray<UFootstepData*> FootstepMappings;
};
