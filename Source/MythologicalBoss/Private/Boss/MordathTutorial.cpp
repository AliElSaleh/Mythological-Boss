// Copyright Overthrone Studios 2019

#include "MordathTutorial.h"

#include "Boss/MordathAnimInstance.h"
#include "Boss/BossAIController.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

#include "Misc/MordathStageData.h"

#include "OverthroneGameState.h"

#include "ConstructorHelpers.h"

#include "FSM.h"

AMordathTutorial::AMordathTutorial()
{
	PrimaryActorTick.bCanEverTick = true;

	// Get our anim blueprint class
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimBP(TEXT("AnimBlueprint'/Game/Characters/Mordath/Animations/ABP_Mordath_Ghost.ABP_Mordath_Ghost_C'"));

	GhostMaterial = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, TEXT("MaterialInstanceConstant'/Game/Art/Materials/VFX/MI_MordathGhostTrail.MI_MordathGhostTrail'")));

	// Configure our mesh
	for (int32 i = 0; i < GetMesh()->GetMaterials().Num(); i++)
		GetMesh()->SetMaterial(i, GhostMaterial);

	if (AnimBP.Succeeded())
		GetMesh()->AnimClass = AnimBP.Class;

	GetCapsuleComponent()->SetCollisionProfileName(FName("Mordath-Ghost"));

	FSM->InitFSM(1);

	Tags.Empty();
	Tags.Add("Mordath-Tutorial");
}

void AMordathTutorial::ResetSelf()
{
	CurrentActionIndex = FMath::RandRange(0, Actions.Num() - 1);

	bCanBeDamaged = true;
	bIsDead = false;
	AnimInstance->bIsDead = false;
	FSM->RemoveAllStates();
}

float AMordathTutorial::GetMovementSpeed() const
{
	switch (RangeFSM->GetActiveStateID())
	{
	case 0 /*Close*/:
		return 500.0f;

	case 1 /*Mid*/:
		return 1000.0f;

	case 2 /*Far*/:
		return 1000.0f;

	default:
		return 0.0f;
	}
}

void AMordathTutorial::LockSelf()
{
	FSM->PushState("Locked");
}

void AMordathTutorial::UnlockSelf()
{
	FSM->PopState("Locked");
}

void AMordathTutorial::BeginPlay()
{
	Super::BeginPlay();

	MordathAnimInstance->CurrentStage = Stage_1;
	MordathAnimInstance->bIsThinking = false;

	CurrentActionIndex = FMath::RandRange(0, Actions.Num() - 1);

	bCanBeDamaged = false;

	FacePlayer_Instant();

	FSM->Start();
	RangeFSM->Start();
}

float AMordathTutorial::TakeDamage(const float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!DamageCauser->IsA(AMordathBase::StaticClass()))
	{
		if (!bIsDead)
			FSM->PushState("Death");
	}

	return DamageAmount;
}

bool AMordathTutorial::CanAttack() const
{
	return !IsAttacking() && IsCloseRange() && !IsLocked();
}

void AMordathTutorial::OnEnterFollowState()
{
	
}

void AMordathTutorial::UpdateFollowState(const float Uptime, const int32 Frames)
{
	FacePlayer();

	if (!IsCloseRange())
		MoveForward();

	if (CanAttack())
	{
		ChooseAction();
	}
}

void AMordathTutorial::OnExitFollowState()
{
}

void AMordathTutorial::OnEnterActionState()
{
	PlayActionMontage();

	StartActionLocation = CurrentLocation;
}

void AMordathTutorial::UpdateActionState(const float Uptime, const int32 Frames)
{
	StopMovement();

	FacePlayer();

	if (AnimInstance->Montage_GetPosition(CurrentActionMontage) >= Actions[CurrentActionIndex].PauseAtTime && !bStopAtTimeEventTriggered)
	{
		bCanBeDamaged = true;

		OnStopAtTimeReached.Broadcast();
		bStopAtTimeEventTriggered = true;
	}

	// If action has finished, go back to previous state
	if (HasFinishedAction())
		FSM->PopState();
}

void AMordathTutorial::OnExitActionState()
{
	// Ensure that anim montage has stopped playing when leaving this state
	StopActionMontage();
}

void AMordathTutorial::OnEnterDeathState()
{
	//Super::OnEnterDeathState();
	
	bStopAtTimeEventTriggered = false;

	PauseAnims();

	OnDeath();

	OnDead.Broadcast();
}

void AMordathTutorial::UpdateDeathState(float Uptime, int32 Frames)
{
	Super::UpdateDeathState(Uptime, Frames);
}

void AMordathTutorial::OnExitDeathState()
{
	AnimInstance->bIsDead = false;

	MovementComponent->SetMovementMode(MOVE_Walking);

	FSM->Start();
}

#pragma region Mordath Tutorial Range States
#pragma region Close Range
void AMordathTutorial::OnEnterCloseRange()
{
}

void AMordathTutorial::UpdateCloseRange(float Uptime, int32 Frames)
{
	if (DistanceToPlayer < 200.0f)
		RangeFSM->PushState("Super Close");

	if (DistanceToPlayer > 500.0f)
		RangeFSM->PushState("Mid");
}

void AMordathTutorial::OnExitCloseRange()
{
}
#pragma endregion

#pragma region Mid Range
void AMordathTutorial::OnEnterMidRange()
{
}

void AMordathTutorial::UpdateMidRange(float Uptime, int32 Frames)
{
	if (DistanceToPlayer < 500.0f)
		RangeFSM->PushState("Close");

	if (DistanceToPlayer > 1200.0f)
		RangeFSM->PushState("Far");
}

void AMordathTutorial::OnExitMidRange()
{
}
#pragma endregion

#pragma region Far Range
void AMordathTutorial::OnEnterFarRange()
{
}

void AMordathTutorial::UpdateFarRange(float Uptime, int32 Frames)
{
	if (DistanceToPlayer < 1200.0f)
	{
		RangeFSM->PushState("Mid");
	}
}

void AMordathTutorial::OnExitFarRange()
{
}
#pragma endregion

#pragma region Super Close Range
void AMordathTutorial::OnEnterSuperCloseRange()
{
}

void AMordathTutorial::UpdateSuperCloseRange(float Uptime, int32 Frames)
{
	if (DistanceToPlayer > 200.0f)
	{
		RangeFSM->PushState("Close");
	}
}

void AMordathTutorial::OnExitSuperCloseRange()
{
}
#pragma endregion
#pragma endregion


void AMordathTutorial::StopActionMontage()
{
	Super::StopActionMontage();

	CurrentMontageSection = "None";
}

void AMordathTutorial::ChooseAction()
{
	if (IsAttacking())
		return;
	
	CurrentActionMontage = Actions[CurrentActionIndex].ActionData->ActionMontage;

	// Update data
	CurrentActionType = Actions[CurrentActionIndex].ActionData->ActionType;
	CurrentCounterType = Actions[CurrentActionIndex].ActionData->CounterType;
	ActionDamage = 0;

	ExecuteAction(Actions[CurrentActionIndex].ActionData);
}

void AMordathTutorial::ExecuteAction(UMordathActionData* ActionData)
{
	StopMovement();

	FSM->PushState("Action");
}
