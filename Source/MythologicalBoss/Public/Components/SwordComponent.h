// Copyright Overthrone Studios 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "SwordComponent.generated.h"

/**
 * A component that can be attached to a character
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), HideCategories=("Activation", "Cooking", "AssetUserData"))
class MYTHOLOGICALBOSS_API USwordComponent final : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	USwordComponent();

	UFUNCTION(BlueprintCallable, Category = "Sword")
		void Glow();

	UFUNCTION(BlueprintCallable, Category = "Sword")
		void PeakGlow();

	// Reverts back to the original sword material
	UFUNCTION(BlueprintCallable, Category = "Sword")
		void Revert();

	UFUNCTION(BlueprintCallable, Category = "Sword")
		class UMaterialInterface* GetDefaultSwordMaterial() const;
protected:
	void BeginPlay() override;

	// The index to assign the glow material to
	UPROPERTY(EditAnywhere, Category = "Sword")
		uint8 MaterialIndex = 0;

	// The name of the paramater from the material instance to track and modify
	UPROPERTY(EditAnywhere, Category = "Sword")
		FName EmissiveParameterName = "Emissive Strength";

	UPROPERTY(EditAnywhere, Category = "Sword")
		float EmissiveStrength = 100.0f;

private:
	class UMaterialInterface* DefaultSwordMaterial;
	class UMaterialInstanceDynamic* MID_SwordMaterial;

	AActor* Owner;
};
