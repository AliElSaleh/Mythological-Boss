// Copyright Overthrone Studios 2019

#include "OverthroneCharacter.h"
#include "Public/OverthroneGameInstance.h"
#include "Public/OverthroneAnimInstance.h"
#include "Public/OverthroneHUD.h"
#include "HUD/FSMVisualizerHUD.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Log.h"
#include "Components/TimelineComponent.h"
#include "Components/HealthComponent.h"

AOverthroneCharacter::AOverthroneCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Health component
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(FName("Health Component"));

	// Take damage timeline component
	TakeDamageTimeline = CreateDefaultSubobject<UTimelineComponent>(FName("Take Damage Timeline"));

	GetCapsuleComponent()->bReturnMaterialOnMove = true;

	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	bCanBeDamaged = true;
}

void AOverthroneCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	InitTimelineComponent(TakeDamageTimeline, TakeDamageCurve, 1.0f, FName("LoseHealth"), FName("FinishLosingHealth"));

	// Store all our child components
	Components = GetComponents();

	// Become vulnerable
	bCanBeDamaged = true;

	//Health = StartingHealth;
	//PreviousHealth = Health;
	//NewHealth = Health;

	// Initialize variables
	World = GetWorld();
	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	MovementComponent = GetCharacterMovement();
	AnimInstance = Cast<UOverthroneAnimInstance>(GetMesh()->GetAnimInstance());
	OverthroneHUD = Cast<AOverthroneHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	GameInstance = Cast<UOverthroneGameInstance>(UGameplayStatics::GetGameInstance(this));
}

void AOverthroneCharacter::UpdateCharacterInfo()
{
	check(0 && "You must implement UpdateCharacterInfo()");
}

void AOverthroneCharacter::InitTimelineComponent(UTimelineComponent* InTimelineComponent, UCurveFloat* InCurveFloat, const float InPlaybackSpeed, const FName& TimelineCallbackFuncName, const FName& TimelineFinishedCallbackFuncName)
{
	// Timeline Initialization
	FOnTimelineFloat TimelineCallback;
	FOnTimelineEvent TimelineFinishedCallback;
	TimelineCallback.BindUFunction(this, TimelineCallbackFuncName);
	TimelineFinishedCallback.BindUFunction(this, TimelineFinishedCallbackFuncName);

	if (InCurveFloat)
	{
		InTimelineComponent = NewObject<UTimelineComponent>(this, InTimelineComponent->GetFName());
		InTimelineComponent->CreationMethod = EComponentCreationMethod::UserConstructionScript;
		InTimelineComponent->SetPropertySetObject(this);
		InTimelineComponent->SetLooping(false);
		InTimelineComponent->SetPlaybackPosition(0.0f, false, false);
		InTimelineComponent->SetPlayRate(InPlaybackSpeed);
		InTimelineComponent->AddInterpFloat(InCurveFloat, TimelineCallback);
		InTimelineComponent->SetTimelineFinishedFunc(TimelineFinishedCallback);
		InTimelineComponent->SetTimelineLength(InCurveFloat->FloatCurve.Keys[InCurveFloat->FloatCurve.Keys.Num() - 1].Time);
		InTimelineComponent->SetTimelineLengthMode(TL_TimelineLength);
		InTimelineComponent->RegisterComponent();
	}
	else
	{
		ULog::DebugMessage(ERROR, "Failed to initialize the " + InTimelineComponent->GetName() + ". A curve float asset is missing!", true);
	}
}

void AOverthroneCharacter::ApplyHitStop()
{

}

void AOverthroneCharacter::ChangeHitboxSize(float NewRadius)
{
	check(0 && "You must implement ChangeHitboxSize()");
}

void AOverthroneCharacter::OnLowHealth()
{
}

void AOverthroneCharacter::StartLosingHealth(const float Amount)
{
	//PreviousHealth = Health;
	//Health -= Amount;
	HealthComponent->DecreaseHealth(Amount);
	TakeDamageTimeline->PlayFromStart();
}

void AOverthroneCharacter::LoseHealth()
{
	const float Time = TakeDamageCurve->GetFloatValue(TakeDamageTimeline->GetPlaybackPosition());

	//NewHealth = FMath::Lerp(PreviousHealth, Health, Time);

	HealthComponent->SetNewHealth(FMath::Lerp(HealthComponent->GetPreviousHealth(), HealthComponent->GetCurrentHealth(), Time));

	UpdateCharacterInfo();
	
	// Are we on low health?
	if (HealthComponent->IsLowHealth() && !bWasLowHealthEventTriggered)
		BroadcastLowHealth();
}

void AOverthroneCharacter::FinishLosingHealth()
{
	//Health = NewHealth;
	//PreviousHealth = Health;

	UpdateCharacterInfo();
}

void AOverthroneCharacter::SetHealth(const float NewHealthAmount)
{
	//PreviousHealth = Health;

	//Health = FMath::Clamp(NewHealthAmount, 0.0f, StartingHealth);
	//NewHealth = Health;

	HealthComponent->SetHealth(NewHealthAmount);

	UpdateCharacterInfo();

	// Are we on low health?
	if (HealthComponent->IsLowHealth() && !bWasLowHealthEventTriggered)
		BroadcastLowHealth();
}

void AOverthroneCharacter::IncreaseHealth(const float Amount)
{
	//PreviousHealth = Health;

	//Health = FMath::Clamp(Health + Amount, 0.0f, StartingHealth);
	//NewHealth = Health;

	HealthComponent->IncreaseHealth(Amount);

	UpdateCharacterInfo();
}

void AOverthroneCharacter::DecreaseHealth(const float Amount)
{
	//PreviousHealth = Health;

	//Health = FMath::Clamp(Health - Amount, 0.0f, StartingHealth);
	//NewHealth = Health;

	HealthComponent->DecreaseHealth(Amount);

	UpdateCharacterInfo();

	// Are we on low health?
	if (HealthComponent->IsLowHealth() && !bWasLowHealthEventTriggered)
		BroadcastLowHealth();
}

void AOverthroneCharacter::ResetHealth()
{
	//Health = StartingHealth;
	//PreviousHealth = Health;
	//NewHealth = Health;
	HealthComponent->ResetHealth();
	UpdateCharacterInfo();
}

void AOverthroneCharacter::Die()
{
	bCanBeDamaged = false;

	AnimInstance->LeaveAllStates();
}

void AOverthroneCharacter::BroadcastLowHealth()
{
	check(0 && "You must implement BroadcastLowHealth()");
}

void AOverthroneCharacter::PauseAnims() const
{
	GetMesh()->bPauseAnims = true;
}

void AOverthroneCharacter::UnPauseAnims() const
{
	GetMesh()->bPauseAnims = false;
}

bool AOverthroneCharacter::IsInvincible() const
{
	return !bCanBeDamaged;
}
