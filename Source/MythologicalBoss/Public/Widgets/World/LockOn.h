// Copyright Overthrone Studios 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LockOn.generated.h"

UCLASS()
class MYTHOLOGICALBOSS_API ALockOn final : public AActor
{
	GENERATED_BODY()
	
public:	
	ALockOn();

	// Set lock-on widget to visible
	UFUNCTION(BlueprintCallable, Category = "Lock-On")
		void Show();
	
	// Set lock-on widget to hidden
	UFUNCTION(BlueprintCallable, Category = "Lock-On")
		void Hide();

	// Toggle lock-on widget visiblility
	UFUNCTION(BlueprintCallable, Category = "Lock-On")
		void ToggleVisibility(bool bVisibility);

protected:
	void BeginPlay() override;

	class UWidgetComponent* LockOnWidgetComponent;
	class ULockOnWidget* LockOnWidget;
};
