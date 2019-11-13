// Copyright Overthrone Studios 2019

#include "MordathStageData.h"

float FThinkStateData::CalculateThinkTime()
{
	const float Min = ThinkTime - RandomDeviation;
	const float Max = ThinkTime + RandomDeviation;

	return FMath::Clamp(FMath::FRandRange(Min, Max), 0.0f, Max);
}

float FRetreatStateData::CalculateRetreatTime()
{
	const float Min = RetreatTime - RandomDeviation;
	const float Max = RetreatTime + RandomDeviation;

	return FMath::Clamp(FMath::FRandRange(Min, Max), 0.0f, Max);
}

void UMordathStageData::Init()
{
	CachedCloseRangeActions = Combat.SuperCloseRangeActions;
	CachedFarRangeActions = Combat.FarRangeActions;
}

float UMordathStageData::GetAttackRadius()
{
	return Combat.AttackSettings.AttackRadius;
}

bool UMordathStageData::IsHitStopEnabled()
{
	return Combat.bEnableHitStop;
}

float UMordathStageData::GetHitStopTime()
{
	return Combat.HitStopTime;
}

UMordathActionData* UMordathStageData::GetRandomSuperCloseRangeAction()
{
	if (CachedCloseRangeActions.Num() == 0)
		Init();

	const int32& Index = FMath::RandRange(0, CachedCloseRangeActions.Num() - 1);

	if (CachedCloseRangeActions.IsValidIndex(Index))
	{
		UMordathActionData* ActionData = CachedCloseRangeActions[Index];
		CachedCloseRangeActions.Remove(ActionData);
		return ActionData;
	}

	return nullptr;
}

UMordathActionData* UMordathStageData::GetRandomFarRangeAction()
{
	if (CachedFarRangeActions.Num() == 0)
		Init();

	const int32& Index = FMath::RandRange(0, CachedFarRangeActions.Num() - 1);

	if (CachedFarRangeActions.IsValidIndex(Index))
	{
		UMordathActionData* ActionData = CachedFarRangeActions[Index];
		CachedFarRangeActions.Remove(ActionData);
		return ActionData;
	}

	return nullptr;
}
