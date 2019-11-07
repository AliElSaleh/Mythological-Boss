// Copyright Overthrone Studios 2019

#include "Managers/OverthroneTutorialManager.h"
#include "UserWidget.h"
#include "TutorialHUD.h"
#include "Log.h"
#include "Kismet/GameplayStatics.h"

AOverthroneTutorialManager::AOverthroneTutorialManager()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AOverthroneTutorialManager::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	TutorialHUD = CreateWidget<UTutorialHUD>(PlayerController, TutorialHUDClass, "Tutorial HUD Widget");
	if (!TutorialHUD)
		ULog::Error("Tutorial HUD is null", true);
}

void AOverthroneTutorialManager::BeginTutorial()
{
	TutorialHUD->AddToViewport();
}

void AOverthroneTutorialManager::EndTutorial()
{
	PlayerController->SetInputMode(FInputModeGameOnly());

	TutorialHUD->EndTutorial();

	Destroy();
}

void AOverthroneTutorialManager::NextTutorial()
{
	OnBeginTutorial.Broadcast();

	PlayerController->SetInputMode(FInputModeGameOnly());

	TutorialHUD->ProgressTutorial();
}
