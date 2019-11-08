// Copyright Overthrone Studios 2019

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "OverthroneStructs.h"
#include "ComboData.h"
#include "MordathStageData.generated.h"

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

	// The camera shake to play when we are damaged
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
		FCameraShakeData LightningStrike;

	// The camera shake to play when entering stage 3
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
		FCameraShakeData Roar;
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
};

USTRUCT(BlueprintType)
struct FAttackSettings_Mordath
{
	GENERATED_BODY()

	// The radius of the capsule collision
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, meta = (ClampMin = 0.0f))
		float AttackRadius = 40.0f;
};

USTRUCT(BlueprintType)
struct FCombatSettings_Mordath : public FCombatSettings
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly)
		FAttackSettings_Mordath AttackSettings;

	// The animation montage to play when in far range on this stage 
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
		TArray<UMordathActionData*> FarRangeActions;

	// The amount of time (in seconds) we wait before initiating the long attack
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
		float FarRangeAttackDelay = 1.0f;

	// The action to randomly play when the player is super close to us
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
		TArray<UMordathActionData*> SuperCloseRangeActions;

	// The animation montage to play when the player is behind us
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
		UMordathActionData* BackHandActionData = nullptr;

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
		float GetAttackRadius();

	UFUNCTION(BlueprintPure, Category = "Mordath | Combat")
		float GetRecentDamage();

	UFUNCTION(BlueprintPure, Category = "Mordath | Combat")
		bool IsHitStopEnabled();

	UFUNCTION(BlueprintPure, Category = "Mordath | Combat")
		float GetHitStopTime();

	UFUNCTION(BlueprintPure, Category = "Mordath")
		FORCEINLINE float GetAttackBlockedBlendOutTime() const { return AttackBlockedBlendOutTime; }

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
		FORCEINLINE FCameraShakeData& GetLightningStrikeShake() { return CameraShakes.LightningStrike; }

	UFUNCTION(BlueprintPure, Category = "Mordath")
		FORCEINLINE FCameraShakeData& GetRoarShake() { return CameraShakes.Roar; }

	UFUNCTION(BlueprintPure, Category = "Mordath")
		FORCEINLINE float GetRecoverTime() const { return RecoverTime; }

	UFUNCTION(BlueprintCallable, Category = "Mordath")
		UMordathActionData* GetRandomSuperCloseRangeAction();

	UFUNCTION(BlueprintCallable, Category = "Mordath")
		UMordathActionData* GetRandomFarRangeAction();

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

	// How long (in seconds) should the boss stay in the recovery state after we've been parried?
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Mordath", meta = (ClampMin = 0.0f))
		float RecoverTime = 1.0f;

	// How long (in seconds) does it take to blend out from our current animation to a staggered animation
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Mordath", meta = (ClampMin = 0.0f))
		float AttackBlockedBlendOutTime = 0.1f;

	// Mordath's movement settings
	UPROPERTY(EditInstanceOnly, Category = "Mordath", DisplayName = "Movement")
		FMovementSettings_Mordath MovementSettings;

	// List of camera shakes
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Mordath")
		FCameraShakes_Mordath CameraShakes;

private:
	TArray<UMordathActionData*> CachedCloseRangeActions;
	TArray<UMordathActionData*> CachedFarRangeActions;
};
