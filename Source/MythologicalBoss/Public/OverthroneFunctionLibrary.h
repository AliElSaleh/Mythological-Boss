// Copyright Overthrone Studios 2019

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "OverthroneFunctionLibrary.generated.h"

/**
 * A list of useful utitly and helpful public funtions exposed to blueprints
 */
UCLASS()
class MYTHOLOGICALBOSS_API UOverthroneFunctionLibrary final : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	// Get the project version string from DefaultGame.ini file
	UFUNCTION(BlueprintPure, Category = "Project Information")
		static FString GetProjectVersion();
	
};
