// Copyright Overthrone Studios 2019

#include "MainPlayerHUD.h"
#include "WidgetTree.h"
#include "ProgressBar.h"
#include "Public/OverthroneGameInstance.h"
#include "Log.h"

void UMainPlayerHUD::Init()
{
	Super::Init();

	GameInstance = Cast<UOverthroneGameInstance>(GetWorld()->GetGameInstance());

	PlayerHealthBar = Cast<UProgressBar>(WidgetTree->FindWidget("Player_Health"));
	PlayerStaminaBar = Cast<UProgressBar>(WidgetTree->FindWidget("Player_Stamina"));
	BossHealthBar = Cast<UProgressBar>(WidgetTree->FindWidget("Boss_Health"));
}

float UMainPlayerHUD::GetPlayerHealthAsPercentage() const
{
	return GameInstance->PlayerHealth / GameInstance->PlayerStartingHealth;
}

float UMainPlayerHUD::GetPlayerStaminaAsPercentage() const
{
	return GameInstance->PlayerStamina / GameInstance->PlayerStartingStamina;
}

float UMainPlayerHUD::GetBossHealthAsPercentage() const
{
	return GameInstance->BossHealth / GameInstance->BossStartingHealth;
}
