// Copyright Ali El Saleh 2019

#include "VideoMenu.h"
#include "GameFramework/GameUserSettings.h"
#include "MenuHUD.h"
#include "OptionsMenu.h"
#include "WidgetTree.h"
#include "TextBlock.h"
#include "VideoSetting.h"
#include "Log.h"

void UVideoMenu::Init()
{
	Super::Init();

	ConfirmationBox = Cast<UUserWidget>(WidgetTree->FindWidget(FName("ConfirmationBox")));

	InitializeSettings();

	InitializeButtons();

	HideWidgets();

	if (bApplyOnLaunch)
		Apply();
}

void UVideoMenu::Back()
{
	if (AnyUnsavedChanges())
	{
		ConfirmationBox->SetVisibility(ESlateVisibility::Visible);

		FString NewMessage;
		if (Changes > 1)
			NewMessage = FString("There are ") + FString::FromInt(Changes) + FString(" unsaved changes. Do you want to apply these changes?");
		else
			NewMessage = FString("There is ") + FString::FromInt(Changes) + FString(" unsaved change. Do you want to apply this change?");

		const auto MessageBox = Cast<UTextBlock>(ConfirmationBox->WidgetTree->FindWidget(FName("Message")));

		MessageBox->SetText(FText::FromString(NewMessage));

		return;
	}

	MenuHUD->HideMenu(StaticClass());

	Super::Back();
}

void UVideoMenu::Apply()
{
	Super::Apply();

	ConfirmationBox->SetVisibility(ESlateVisibility::Hidden);

	if (Changes > 0)
	{
		MenuHUD->HideMenu(StaticClass());
		Super::Back();
	}

	ChangedSettings.Empty();
	Changes = 0;
}

void UVideoMenu::InitializeButtons()
{
	Super::InitializeButtons();

	// Initialise the buttons in the confirmation box
	const auto ApplyButton = Cast<UButtonBase>(ConfirmationBox->WidgetTree->FindWidget(FName("ConfirmApply")));
	const auto DiscardButton = Cast<UButtonBase>(ConfirmationBox->WidgetTree->FindWidget(FName("ConfirmDiscard")));
	
	ApplyButton->Init();
	DiscardButton->Init();
}

void UVideoMenu::DiscardChanges()
{
	for (auto Setting : ChangedSettings)
	{
		Setting->RevertChange();
	}

	ConfirmationBox->SetVisibility(ESlateVisibility::Hidden);
	ChangedSettings.Empty();
	Changes = 0;

	MenuHUD->HideMenu(StaticClass());
	Super::Back();
}

void UVideoMenu::GoBack()
{
	MenuHUD->ShowMenu(UOptionsMenu::StaticClass());

	Super::GoBack();
}

void UVideoMenu::HideWidgets()
{
	ConfirmationBox->SetVisibility(ESlateVisibility::Hidden);
}

bool UVideoMenu::AnyUnsavedChanges()
{
	for (auto Setting : MenuSettings)
	{
		if (Setting->HasChanged())
		{
			ULog::LogDebugMessage(INFO, Setting->GetName() + FString(" has changed"), true);
			ChangedSettings.Add(Setting);
			Changes++;
		}
	}
	
	ULog::LogDebugMessage(INFO, FString::FromInt(Changes) + FString(" Changes found"), true);

	return Changes > 0;
}
