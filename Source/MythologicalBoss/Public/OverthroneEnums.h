// Copyright Overthrone Studios 2019

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"

UENUM()
enum EBuildConfig
{
	DebugBuild,
	DevelopmentBuild,
	ShippingBuild
};

UENUM()
enum EDashType_Mordath
{
	Dash_Forward,
	Dash_Backward,
	Dash_Left,
	Dash_Right
};

UENUM(BlueprintType)
enum EBossStage_Mordath
{
	Stage_1,
	Stage_2,
	Stage_3
};

UENUM()
enum EAttackType_Player
{
	Light,
	Heavy,
	Special,
	EATP_None UMETA(DisplayName="None")
};

UENUM()
enum EActionType_Mordath
{
	ShortAttack_1,
	ShortAttack_2,
	ShortAttack_3,
	LongAttack_1,
	LongAttack_2,
	LongAttack_3,
	SpecialAttack_1,
	SpecialAttack_2,
	SpecialAttack_3,
	Kick,
	BackHand,
	EATM_None UMETA(DisplayName="None")
};

UENUM()
enum EAttackCounters_Mordath
{
	Parryable,
	Blockable,
	ParryableBlockable,
	NoCounter,
	EACM_None UMETA(DisplayName="None")
};

UENUM()
enum EBossRanges
{
	SuperClose,
	Close,
	Mid,
	Far
};

/**
 * A header file containing all enums that Overthrone uses
 */
class MYTHOLOGICALBOSS_API UOverthroneEnums
{
public:
	UOverthroneEnums() = default;
	~UOverthroneEnums() = default;

	static FString MordathAttackTypeToString(const EActionType_Mordath& Enum);
	static FString MordathAttackCounterTypeToString(const EAttackCounters_Mordath& Enum);
};
