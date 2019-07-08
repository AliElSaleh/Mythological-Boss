// Copyright Overthrone Studios 2019

#pragma once

#include "Engine/GameInstance.h"
#include "OverthroneGameInstance.generated.h"

/**
 * High-level manager object for the Overthrone game instance
 */
UCLASS()
class MYTHOLOGICALBOSS_API UOverthroneGameInstance final : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UOverthroneGameInstance();

private:
	class USoundClass* MasterSoundClass;
	class USoundClass* MusicSoundClass;
	class USoundClass* SFXSoundClass;
	class USoundClass* UISoundClass;
	class USoundMix* MasterMix;
};
