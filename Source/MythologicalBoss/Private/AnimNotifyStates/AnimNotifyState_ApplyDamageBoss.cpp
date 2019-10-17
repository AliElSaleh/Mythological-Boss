// Copyright Overthrone Studios 2019

#include "AnimNotifyStates/AnimNotifyState_ApplyDamageBoss.h"
#include "ApexDestruction/Public/DestructibleActor.h"
#include "Animation/AnimSequenceBase.h"
#include "HitSoundData.h"
#include "Mordath.h"
#include "Log.h"
#include "Kismet/GameplayStatics.h"
#include "MordathGhost.h"

void UAnimNotifyState_ApplyDamageBoss::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Mordath = Cast<AMordath>(MeshComp->GetOwner());

	if (!Mordath)
	{
		MordathGhost = Cast<AMordathGhost>(MeshComp->GetOwner());

		if (!MordathGhost)
			return;

		AttackRadius = MordathGhost->GetAttackRadius();

		if (MordathGhost->IsShortAttacking())
			AttackDamage = MordathGhost->GetShortAttackDamage();
		else if (MordathGhost->IsLongAttacking())
			AttackDamage = MordathGhost->GetLongAttackDamage();
		else if (MordathGhost->IsSpecialAttacking())
			AttackDamage = MordathGhost->GetSpecialAttackDamage();

		return;
	}

#if !UE_BUILD_SHIPPING
	if (Mordath->Debug.bShowRaycasts)
		DebugTrace = EDrawDebugTrace::ForDuration;
	else
		DebugTrace = EDrawDebugTrace::None;
#endif

	AttackRadius = Mordath->GetAttackRadius();
	AttackDamage = Mordath->GetActionDamage();

#if !UE_BUILD_SHIPPING
	if (HitSoundData && HitSoundData->HitSounds.Num() == 0)
		ULog::Warning("No hit sounds specified in " + Animation->GetName(), true);
#endif
}

void UAnimNotifyState_ApplyDamageBoss::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	bIsHit = false;
}

void UAnimNotifyState_ApplyDamageBoss::OnHit(USkeletalMeshComponent* MeshComp)
{
	const auto HitActor = HitResult.GetActor();
	const auto HitComponent = HitResult.GetComponent();
	const FDamageEvent DamageEvent;

	if (HitComponent && Mordath)
		HitComponent->OnComponentHit.Broadcast(HitResult.GetComponent(), Mordath, MeshComp, HitResult.ImpactNormal, HitResult);

	if (HitActor && Mordath)
		UGameplayStatics::SpawnForceFeedbackAtLocation(MeshComp, Mordath->GetCurrentForceFeedbackEffect(), HitResult.Location);

	if (HitActor && (HitActor->IsA(ACharacter::StaticClass()) && HitActor->bCanBeDamaged) && Mordath && !Mordath->IsDamaged())
	{
		bIsHit = true;

		// Apply hit stop
		if (Mordath)
			Mordath->PauseAnimsWithTimer();
		else if (MordathGhost)
			MordathGhost->PauseAnimsWithTimer();

		HitActor->TakeDamage(AttackDamage, DamageEvent, MeshComp->GetOwner()->GetInstigatorController(), MeshComp->GetOwner());

		if (Mordath && !Mordath->IsDamaged() && !Mordath->IsStunned())
		{
			// Play sound effect
			PlayHitSound(MeshComp);

			Mordath->OnAttackLanded(HitResult);
		}
		else if(MordathGhost)
		{
			// Play sound effect
			PlayHitSound(MeshComp);
		}
	}
}
