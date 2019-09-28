// Copyright Overthrone Studios 2019

#include "MordathActionData.h"

FString UMordathActionData::GetCounterTypeAsString() const
{
	switch (CounterType)
	{
	case Parryable:
		return FString("Parryable");

	case Blockable:
		return FString("Blockable");

	case NoCounter:
		return FString("No Counter");

	default:
		return FString("None");
	}
}

FString UMordathActionData::GetCurrentActionAsString() const
{
	// Choose the current attack from the attack data
	switch (ActionType)
	{
	case ATM_ShortAttack_1:
		return FString("Short Attack 1");

	case ATM_ShortAttack_2:
		return FString("Short Attack 2");

	case ATM_ShortAttack_3:
		return FString("Short Attack 3");

	case ATM_LongAttack_1:
		return FString("Long Attack 1");

	case ATM_LongAttack_2:
		return FString("Long Attack 2");

	case ATM_LongAttack_3:
		return FString("Long Attack 3");

	case ATM_SpecialAttack_1:
		return FString("Special Attack 1");

	case ATM_SpecialAttack_2:
		return FString("Special Attack 2");

	case ATM_SpecialAttack_3:
		return FString("Special Attack 3");

	case ATM_Kick:
		return FString("Kick");

	case ATM_BackHand:
		return FString("Back Hand");

	case ATM_Strafe_Left:
		return FString("Strafe Left");

	case ATM_Strafe_Right:
		return FString("Strafe Right");

	case ATM_Dash_Forward:
		return FString("Dash Forward");

	case ATM_Dash_Backward:
		return FString("Dash Backward");

	case ATM_Dash_Left:
		return FString("Dash Left");

	case ATM_Dash_Right:
		return FString("Dash Right");

	case ATM_Teleport:
		return FString("Teleport");

	case ATM_Tired:
		return FString("Tired");

	default:
		return FString("None");
	}
}
