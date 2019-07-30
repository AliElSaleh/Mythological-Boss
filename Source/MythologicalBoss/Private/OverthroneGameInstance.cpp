// Copyright Overthrone Studios 2019

#include "OverthroneGameInstance.h"
#include "UserWidget.h"
#include "LockOn.h"
#include "Kismet/GameplayStatics.h"
#include "ConstructorHelpers.h"
#include "Log.h"

UOverthroneGameInstance::UOverthroneGameInstance()
{
	static ConstructorHelpers::FClassFinder<UWidget> PauseMenuWidget(TEXT("WidgetBlueprint'/Game/UI/Menus/UI_PauseMenu.UI_PauseMenu_C'"));

	if (PauseMenuWidget.Succeeded())
		PauseMenuWidgetClass = PauseMenuWidget.Class;
}

bool UOverthroneGameInstance::IsGamePaused()
{
	return UGameplayStatics::IsGamePaused(this);
}

void UOverthroneGameInstance::PauseGame()
{
	PauseMenu->SetVisibility(ESlateVisibility::Visible);
	PauseMenu->SetKeyboardFocus();

	SetInputModeUI();

	UGameplayStatics::SetGamePaused(this, true);
}

void UOverthroneGameInstance::UnPauseGame()
{
	PauseMenu->SetVisibility(ESlateVisibility::Hidden);

	SetInputModeGame();

	UGameplayStatics::SetGamePaused(this, false);
}

void UOverthroneGameInstance::SetInputModeUI() const
{
	const FInputModeUIOnly InputModeUIOnly;
	PlayerController->SetInputMode(InputModeUIOnly);
	PlayerController->bShowMouseCursor = true;
}

void UOverthroneGameInstance::SetInputModeGame() const
{
	const FInputModeGameOnly InputModeGameOnly;
	PlayerController->SetInputMode(InputModeGameOnly);
	PlayerController->bShowMouseCursor = false;
}

void UOverthroneGameInstance::InitInstance()
{
	PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	PauseMenu = CreateWidget<UUserWidget>(GetWorld(), PauseMenuWidgetClass, FName("Pause Menu"));
	PauseMenu->AddToViewport();
	PauseMenu->SetVisibility(ESlateVisibility::Hidden);
}

void UOverthroneGameInstance::SetLockOnLocation(const FVector& LockOnLocation) const
{
	if (LockOn)
		LockOn->SetActorLocation(LockOnLocation);
	else
		ULog::LogDebugMessage(WARNING, FString("LockOn actor does not exist in the world"), true);
}

void UOverthroneGameInstance::SetLockOnRotation(const FRotator& LockOnRotation) const
{
	if (LockOn)
		LockOn->SetActorRotation(LockOnRotation);
	else
		ULog::LogDebugMessage(WARNING, FString("LockOn actor does not exist in the world"), true);
}

void UOverthroneGameInstance::ToggleLockOnVisibility(const bool bIsVisible) const
{
	if (LockOn)
		LockOn->SetActorHiddenInGame(bIsVisible);
	else
		ULog::LogDebugMessage(WARNING, FString("LockOn actor does not exist in the world"), true);
}
