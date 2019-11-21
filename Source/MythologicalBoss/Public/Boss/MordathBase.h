// Copyright Overthrone Studios 2019

#pragma once

#include "CoreMinimal.h"
#include "OverthroneCharacter.h"
#include "ComboData.h"
#include "MordathBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnterPerfectDashSignature);

UCLASS(Abstract)
class MYTHOLOGICALBOSS_API AMordathBase : public AOverthroneCharacter
{
	GENERATED_BODY()

public:
	AMordathBase();

	FOnEnterPerfectDashSignature OnEnterPerfectDash;

	UFUNCTION(BlueprintPure, Category = "Mordath | General")
		float GetDistanceToPlayer() const;

	UFUNCTION(BlueprintPure, Category = "Mordath | General")
		FVector GetDirectionToPlayer() const;

	// Returns true if we are super close to the player
	UFUNCTION(BlueprintPure, Category = "Mordath | General")
		bool IsSuperCloseRange() const;

	// Returns true if we are in close distance to the player
	UFUNCTION(BlueprintPure, Category = "Mordath | General")
		bool IsCloseRange() const;

	// Returns true if we are in mid distance to the player
	UFUNCTION(BlueprintPure, Category = "Mordath | General")
		bool IsMidRange() const;

	// Returns true if we are in far distance to the player
	UFUNCTION(BlueprintPure, Category = "Mordath | General")
		bool IsFarRange() const;

	float GetActionDamage() const override;

	bool IsAttacking() const override;

	UFUNCTION(BlueprintPure, Category = "Mordath | Combat")
		bool IsShortAttacking() const;
	
	UFUNCTION(BlueprintPure, Category = "Mordath | Combat")
		bool IsLongAttacking() const;
	
	UFUNCTION(BlueprintPure, Category = "Mordath | Combat")
		bool IsSpecialAttacking() const;

	UFUNCTION(BlueprintPure, Category = "Mordath | Combat")
		bool IsDelayingAction() const;

	UFUNCTION(BlueprintPure, Category = "Mordath | Combat")
		bool IsIdling() const;

	UFUNCTION(BlueprintPure, Category = "Mordath | Combat")
		bool IsFollowing() const;

	UFUNCTION(BlueprintPure, Category = "Mordath | Combat")
		bool IsThinking() const;

	UFUNCTION(BlueprintPure, Category = "Mordath | Combat")
		bool IsPerformingAction() const;

	// Returns true if the time to execute has been reached
	UFUNCTION(BlueprintPure, Category = "Mordath | Combat")
		bool IsExecutionTimeExpired() const;

	bool IsLocked() const override;

	UFUNCTION(BlueprintPure, Category = "Mordath | Combat")
		UForceFeedbackEffect* GetCurrentForceFeedbackEffect() const;

	UFUNCTION(BlueprintCallable, Category = "Mordath | Combat")
		void RemoveFromLockOnTargetsArray();
	
	UFUNCTION(BlueprintCallable, Category = "Mordath | Combat")
		void AddToLockOnTargetsArray();

	void Die() override;

protected:
	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void Tick(float DeltaTime) override;
	void PossessedBy(AController* NewController) override;

	void StopMovement() override;

	void OnExecutionTimeExpired();

	class UMordathFeatherComponent* GetFeathers() const;

	UFUNCTION(BlueprintCallable, Category = "Mordath | General")
		void FacePlayer(float RotationSpeed = 5.0f);

	UFUNCTION(BlueprintCallable, Category = "Mordath | General")
		void FacePlayer_Instant();

	UFUNCTION(BlueprintCallable, Category = "Mordath | General")
		void FacePlayerBasedOnActionData(const class UMordathActionData* ActionData);

	UFUNCTION(BlueprintCallable, Category = "Mordath | Movement")
		void MoveForward(float Scale = 1.0f);

	UFUNCTION(BlueprintCallable, Category = "Mordath | Movement")
		void MoveRight(float Scale = 1.0f);

	UFUNCTION(BlueprintCallable, Category = "Mordath | Movement")
		void ChooseMovementDirection();

	float GetMovementSpeed() const override;

	UFUNCTION(BlueprintPure, Category = "Mordath | Movement")
		bool WantsMoveRight() const;

	UFUNCTION(BlueprintCallable, Category = "Mordath | Movement")
		void EncirclePlayer();

	UFUNCTION(BlueprintCallable, Category = "Mordath | Combat")
		void PlayActionMontage();

	void PlayActionMontage(class UMordathActionData* ActionData);

	UFUNCTION(BlueprintCallable, Category = "Mordath | Combat")
		virtual void StopActionMontage();

	UFUNCTION(BlueprintCallable, Category = "Mordath | Combat")
		virtual void ChooseCombo();
	
	UFUNCTION(BlueprintCallable, Category = "Mordath | Combat")
		virtual float ChooseComboDelayed();

	// Returns true if we the combo delay timer is active
	UFUNCTION(BlueprintPure, Category = "Mordath | Combat")
		bool IsWaitingForNextCombo() const;

	UFUNCTION(BlueprintCallable, Category = "Mordath | Combat")
		virtual void ChooseAction();

	UFUNCTION(BlueprintCallable, Category = "Mordath | Combat")
		virtual void ExecuteAction(class UMordathActionData* ActionData);

	UFUNCTION(BlueprintPure, Category = "Mordath | Combat")
		virtual bool CanAttack() const;

	UFUNCTION(BlueprintCallable, Category = "Mordath | Combat")
		virtual void NextAction();

	UFUNCTION(BlueprintCallable, Category = "Mordath | Combat")
		void StartExecutionExpiryTimer();

	// Returns true if we have finished playing our current action montage
	UFUNCTION(BlueprintPure, Category = "Mordath | Combat")
		bool HasFinishedAction() const;
		bool HasFinishedAction(class UAnimMontage* ActionMontage) const;

	UFUNCTION(BlueprintCallable, Category = "Mordath | Combat")
		void IncreaseAttackDamage(const float& Multiplier);

	UFUNCTION(BlueprintCallable, Category = "Mordath | Combat")
		void ResetActionDamage();

	UFUNCTION(BlueprintCallable, Category = "Mordath | Combat")
		void SpawnPerfectDashEmitter();

	#pragma region Mordath Base Any States
		#pragma region Main FSM
		UFUNCTION()
			virtual void OnEnterAnyState(int32 ID, FName Name);
		UFUNCTION()
			virtual void UpdateAnyState(int32 ID, FName Name, float Uptime, int32 Frames);
		UFUNCTION()
			virtual void OnExitAnyState(int32 ID, FName Name);
		#pragma endregion 

		#pragma region Range FSM
		UFUNCTION()
			virtual void OnEnterAnyRangeState(int32 ID, FName Name);
		UFUNCTION()
			virtual void UpdateAnyRangeState(int32 ID, FName Name, float Uptime, int32 Frames);
		UFUNCTION()
			virtual void OnExitAnyRangeState(int32 ID, FName Name);
		#pragma endregion 
	#pragma endregion 

	#pragma region Mordath Base States
		#pragma region Idle
			UFUNCTION()
				virtual void OnEnterIdleState();
			UFUNCTION()
				virtual void UpdateIdleState(float Uptime, int32 Frames);
			UFUNCTION()
				virtual void OnExitIdleState();
		#pragma endregion 

		#pragma region Follow
			UFUNCTION()
				virtual void OnEnterFollowState();
			UFUNCTION()
				virtual void UpdateFollowState(float Uptime, int32 Frames);
			UFUNCTION()
				virtual void OnExitFollowState();
		#pragma endregion 

		#pragma region Think
			UFUNCTION()
				virtual void OnEnterThinkState();
			UFUNCTION()
				virtual void UpdateThinkState(float Uptime, int32 Frames);
			UFUNCTION()
				virtual void OnExitThinkState();
		#pragma endregion 

		#pragma region Action
			UFUNCTION()
				virtual void OnEnterActionState();
			UFUNCTION()
				virtual void UpdateActionState(float Uptime, int32 Frames);
			UFUNCTION()
				virtual void OnExitActionState();
		#pragma endregion 
	#pragma endregion 

	#pragma region Mordath Base Range States
		#pragma region Close
		UFUNCTION()
			virtual void OnEnterCloseRange();
		UFUNCTION()
			virtual void UpdateCloseRange(float Uptime, int32 Frames);
		UFUNCTION()
			virtual void OnExitCloseRange();
		#pragma endregion 

		#pragma region Mid
		UFUNCTION()
			virtual void OnEnterMidRange();
		UFUNCTION()
			virtual void UpdateMidRange(float Uptime, int32 Frames);
		UFUNCTION()
			virtual void OnExitMidRange();
		#pragma endregion 

		#pragma region Far
		UFUNCTION()
			virtual void OnEnterFarRange();
		UFUNCTION()
			virtual void UpdateFarRange(float Uptime, int32 Frames);
		UFUNCTION()
			virtual void OnExitFarRange();

		UFUNCTION()
			virtual void OnEnterSuperCloseRange();
		UFUNCTION()
			virtual void UpdateSuperCloseRange(float Uptime, int32 Frames);
		UFUNCTION()
			virtual void OnExitSuperCloseRange();
		#pragma endregion 
	#pragma endregion

	// Called when the player's health is less than or equal to 0
	UFUNCTION()
		virtual void OnPlayerDeath();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mordath")
		class UMordathFeatherComponent* SKM_Feathers;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Mordath Combat")
		UParticleSystem* PerfectDashParticle;

	UPROPERTY(BlueprintReadOnly, Category = "Mordath | Combat")
		class UAnimMontage* CurrentActionMontage;

	UPROPERTY(BlueprintReadOnly, Category = "Mordath | Combat")
		class UMordathStageData* CurrentStageData;

	// The combo we are using
	UPROPERTY(BlueprintReadOnly, Category = "Mordath | Combat")
		UComboData* ChosenCombo;

	// Used to iterate, select or remove a combo, this to avoid touching the actual combos list
	UPROPERTY(BlueprintReadOnly, Category = "Mordath | Combat")
		TArray<UComboData*> CachedCombos;

	UPROPERTY(BlueprintReadOnly, Category = "Mordath | General")
		class AOverthroneCharacter* PlayerCharacter;

	// The boss's range Finite State Machine
	UPROPERTY(BlueprintReadOnly, Category = "Mordath | General")
		class UFSM* RangeFSM;

	UPROPERTY(BlueprintReadOnly, Category = "Mordath | General")
		float DistanceToPlayer = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Mordath | General")
		FVector DirectionToPlayer = FVector(0.0f);

	// Our custom AI controller
	UPROPERTY(BlueprintReadOnly, Category = "Mordath | AI")
		class ABossAIController* BossAIController{};
	
	// Cached anim instance, to control and trigger animations
	UPROPERTY(BlueprintReadOnly, Category = "Mordath | Animation")
		class UMordathAnimInstance* MordathAnimInstance{};

	// The skeletal mesh representing the feathers
	USkeletalMesh* FeatherSkeletalMesh;

	UAnimationAsset* FeatherAnim;

	FName CurrentMontageSection = "None";

	FVector StartActionLocation;
	FVector EndActionLocation;

	FComboData_Action* CurrentActionData;

	EActionType_Mordath CurrentActionType;
	EAttackCounters_Mordath CurrentCounterType;

	uint8 MovementDirection : 1;

	uint8 bPerfectDashEmitterSpawned : 1;

	FTimerHandle TH_NextComboDelay;
};
