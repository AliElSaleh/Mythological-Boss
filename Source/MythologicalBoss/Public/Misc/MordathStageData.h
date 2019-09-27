// Copyright Overthrone Studios 2019

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "OverthroneStructs.h"
#include "ComboData.h"
#include "MordathStageData.generated.h"

USTRUCT(BlueprintType)
struct FThinkStateData
{
	GENERATED_BODY()

	// Calculates a new think time using RandomDeviation
	float CalculateThinkTime();

protected:
	// How long (in seconds) should the boss think for, before initiating an attack?
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta = (ClampMin = 0.0f, ClampMax = 60.0f))
		float ThinkTime = 2.0f;

	// Adds a random range to ThinkTime
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta = (ClampMin = 0.0f))
		float RandomDeviation = 0.3f;
};

USTRUCT(BlueprintType)
struct FRetreatStateData
{
	GENERATED_BODY()

	// Calculates a new retreat time using RandomDeviation
	float CalculateRetreatTime();
		
protected:
	// How long (in seconds) should the boss move away from you (walk backwards)?
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta = (ClampMin = 0.0f, ClampMax = 60.0f))
		float RetreatTime = 1.0f;

	// Adds a random range to RetreatTime
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta = (ClampMin = 0.0f))
		float RandomDeviation = 0.3f;
};

USTRUCT(BlueprintType)
struct FCameraShakes_Mordath
{
	GENERATED_BODY()

	// The camera shake to play when we are damaged
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
		FCameraShakeData Damaged;

	// The camera shake to play when we are damaged
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
		FCameraShakeData Stun;
};

USTRUCT(BlueprintType)
struct FMovementSettings_Mordath
{
	GENERATED_BODY()

	// The maximum movement speed while walking
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta = (ClampMin = 1.0f, ClampMax = 10000.0f))
		float WalkSpeed = 500.0f;

	// The movement speed of the boss when we're at mid range distance from the player
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta = (ClampMin = 0.0f, ClampMax = 1000000.0f))
		float RunSpeed = 800.0f;

	// The distance away from the player where we can dash forwards
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta = (ClampMin = 0.0f, ClampMax = 10000.0f))
		float DashAtDistance = 800.0f;
};

USTRUCT(BlueprintType)
struct FComboSettings
{
	GENERATED_BODY()

	// Should the boss wait before initiating the next combo?
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
		uint8 bDelayBetweenCombo : 1;

	// The time in seconds to delay before choosing a new combo
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta = (EditCondition = "bDelayBetweenCombo", ClampMin = 0.0f, ClampMax = 10.0f))
		float ComboDelayTime = 1.0f;

	// Adds a random range to ComboDelayTime
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta = (EditCondition = "bDelayBetweenCombo", ClampMin = 0.0f, ClampMax = 10.0f))
		float RandomDeviation = 0.1f;

	// Should the boss choose a random combo from the Combos list?
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
		uint8 bChooseRandomCombo : 1;

	// A list of combos the boss character will choose from when in the first stage
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
		TArray<UComboData*> Combos;

	// The animation montage to play when in far range on stage 1
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta = (ClampMin = 0.0f))
		class UAnimMontage* FarRangeAttackAnim = nullptr;

	// The amount of time (in seconds) we wait before initiating the long attack
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
		float FarRangeAttackDelay = 1.0f;
};

USTRUCT(BlueprintType)
struct FAttackSettings_Mordath : public FAttackSettings
{
	GENERATED_BODY()

	// The attack damage we deal when heavy attacking
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta = (ClampMin = 0.0f, ClampMax = 10000.0f))
		float SpecialAttackDamage = 60.0f;
};

USTRUCT(BlueprintType)
struct FCombatSettings_Mordath : public FCombatSettings
{
	GENERATED_BODY()

protected:
	// Settings that affect Mordath's attack values
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, DisplayName = "Attack")
		FAttackSettings_Mordath AttackSettings;

public:
	FAttackSettings_Mordath& GetAttackSettings() { return AttackSettings; }

	// The amount of time in seconds this boss should be stunned for
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta = (ClampMin = 0.0f, ClampMax = 10.0f))
		float StunDuration = 0.8f;

	// Maximum hits that can be taken before becoming invincible
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta = (ClampMin = 0, ClampMax = 100))
		uint8 MaxHitsBeforeInvincibility = 3;

	// The amount of time (in seconds) that the boss can stay invincible after being damaged by the player
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta = (ClampMin = 0.01f, ClampMax = 100.0f))
		float InvincibilityTimeAfterDamage = 1.5f;

	// The flash color to set when our current attack has no counter
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
		FLinearColor NoCounterFlashColor = FLinearColor(1.0f, 0.0f, 0.0f, 0.2f);

	// The flash color to set when our current attack has is parryable
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
		FLinearColor ParryableFlashColor = FLinearColor(1.0f, 1.0f, 0.0f, 0.2f);

	// The flash color to set when our current attack has is blockable
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
		FLinearColor BlockableFlashColor = FLinearColor(1.0f, 1.0f, 1.0f, 0.2f);

	float RecentDamage = 0.0f;
};

/**
 * Mordath's stage behaviour data
 */
UCLASS()
class MYTHOLOGICALBOSS_API UMordathStageData final : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Mordath | Combat")
		void Init();

	UFUNCTION(BlueprintPure, Category = "Mordath | Combat")
		float GetShortAttackDamage();

	UFUNCTION(BlueprintPure, Category = "Mordath | Combat")
		float GetLongAttackDamage();

	UFUNCTION(BlueprintPure, Category = "Mordath | Combat")
		float GetSpecialAttackDamage();

	UFUNCTION(BlueprintPure, Category = "Mordath | Combat")
		float GetAttackRadius();

	UFUNCTION(BlueprintPure, Category = "Mordath | Combat")
		float GetAttackRadiusOnLowHealth();

	UFUNCTION(BlueprintCallable, Category = "Mordath | Combat")
		void SetAttackRadius(const float& NewRadius);

	UFUNCTION(BlueprintPure, Category = "Mordath | Combat")
		float GetRecentDamage();

	UFUNCTION(BlueprintPure, Category = "Mordath | Combat")
		bool IsHitStopEnabled();

	UFUNCTION(BlueprintPure, Category = "Mordath | Combat")
		float GetHitStopTime();

	UFUNCTION(BlueprintPure, Category = "Mordath")
		FORCEINLINE float GetCloseRangeRadius() const { return AcceptanceRadius; }

	UFUNCTION(BlueprintPure, Category = "Mordath")
		FORCEINLINE float GetSuperCloseRangeRadius() const { return SuperCloseRadius; }

	UFUNCTION(BlueprintPure, Category = "Mordath")
		FORCEINLINE float GetMidRangeRadius() const { return MidRangeRadius; }

	UFUNCTION(BlueprintPure, Category = "Mordath")
		FORCEINLINE float GetSuperCloseRangeTime() const { return SuperCloseRangeTime; }

	UFUNCTION(BlueprintPure, Category = "Mordath")
		FORCEINLINE float GetWalkSpeed() const { return MovementSettings.WalkSpeed; }
	
	UFUNCTION(BlueprintPure, Category = "Mordath")
		FORCEINLINE float GetRunSpeed() const { return MovementSettings.RunSpeed; }
	
	UFUNCTION(BlueprintPure, Category = "Mordath")
		FORCEINLINE float GetDashDistanceThreshold() const { return MovementSettings.DashAtDistance; }

	UFUNCTION(BlueprintPure, Category = "Mordath")
		FORCEINLINE float GetAttackDamageMultiplier() const { return DamageMultiplierOnSuperCloseRange; }

	UFUNCTION(BlueprintPure, Category = "Mordath")
		FORCEINLINE FCameraShakeData& GetDamagedShake() { return CameraShakes.Damaged; }

	UFUNCTION(BlueprintPure, Category = "Mordath")
		FORCEINLINE FCameraShakeData& GetStunShake() { return CameraShakes.Stun; }

	UFUNCTION(BlueprintPure, Category = "Mordath")
		FORCEINLINE uint8 GetRecoverLoops() const { return RecoverLoops; }

	// Holds the data relating to the 'Think' state
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Mordath")
		FThinkStateData ThinkStateData;
	
	// Holds the data relating to the 'Retreat' state (i.e Walking backwards)
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Mordath")
		FRetreatStateData RetreatStateData;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Mordath Combat")
		FComboSettings ComboSettings;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Mordath Combat")
		FCombatSettings_Mordath Combat;

protected:
	// The radius in which the boss character will accept that it has arrived to the player's location
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Mordath", meta = (ClampMin = 1.0f, ClampMax = 100000.0f), DisplayName = "Close Range Radius")
		float AcceptanceRadius = 200.0f;

	// The radius in which the boss character will increase their damage by a factor
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Mordath", meta = (ClampMin = 1.0f, ClampMax = 100000.0f))
		float SuperCloseRadius = 200.0f;

	// The factor to multiply all the attack damages by
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Mordath", meta = (ClampMin = 1.0f))
		float DamageMultiplierOnSuperCloseRange = 1.5f;

	// The radius of the mid range area
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Mordath", meta = (ClampMin = 1.0f, ClampMax = 100000.0f))
		float MidRangeRadius = 400.0f;

	// How long (in seconds) should the boss stay close to the player before dashing away?
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Mordath", meta = (ClampMin = 0.01f, ClampMax = 100000.0f))
		float SuperCloseRangeTime = 2.0f;

	// How many loops should we do when recovering
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Mordath", meta = (ClampMin = 0))
		uint8 RecoverLoops = 1;

	// Mordath's movement settings
	UPROPERTY(EditInstanceOnly, Category = "Mordath", DisplayName = "Movement")
		FMovementSettings_Mordath MovementSettings;

	// List of camera shakes
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Mordath")
		FCameraShakes_Mordath CameraShakes;
};
