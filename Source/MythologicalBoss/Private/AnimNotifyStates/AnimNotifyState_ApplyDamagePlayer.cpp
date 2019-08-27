// Copyright Overthrone Studios 2019

#include "AnimNotifyStates/AnimNotifyState_ApplyDamagePlayer.h"
#include "DestructibleActor.h"
#include "Ylva.h"
#include "Log.h"

void UAnimNotifyState_ApplyDamagePlayer::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Ylva = Cast<AYlva>(MeshComp->GetOwner());

	if (!Ylva)
		return;

	if (Ylva->Debug.bShowRaycasts)
		DebugTrace = EDrawDebugTrace::ForDuration;
	else
		DebugTrace = EDrawDebugTrace::None;

	AttackRadius = Ylva->GetAttackRadius();

	if (Ylva->IsLightAttacking())
		AttackDamage = Ylva->GetLightAttackDamage();
	else if (Ylva->IsHeavyAttacking())
		AttackDamage = Ylva->GetHeavyAttackDamage();
}

void UAnimNotifyState_ApplyDamagePlayer::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	bIsHit = false;
}

void UAnimNotifyState_ApplyDamagePlayer::OnHit(USkeletalMeshComponent* MeshComp)
{
	const auto HitActor = HitResult.GetActor();
	const FDamageEvent DamageEvent;

	if (HitActor && (HitActor->IsA(ACharacter::StaticClass()) || HitActor->IsA(ADestructibleActor::StaticClass())))
	{
		bIsHit = true;

		Ylva->ApplyHitStop();

		// Give charge
		Ylva->IncreaseCharge();

		const auto HitComp = HitResult.GetComponent();
		ULog::Info(HitComp->GetName(), true);

		HitActor->TakeDamage(AttackDamage, DamageEvent, MeshComp->GetOwner()->GetInstigatorController(), MeshComp->GetOwner());
	}
}
