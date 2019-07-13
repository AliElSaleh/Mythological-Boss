// Copyright Ali El Saleh 2019

#include "DisplayModeSetting.h"
#include "WidgetTree.h"
#include "ComboBoxString.h"

void UDisplayModeSetting::PopulateDisplayModeList(UComboBoxString* DropDownList)
{
	DropDownList->AddOption(FString("Windowed"));
	DropDownList->AddOption(FString("Windowed Fullscreen"));
	DropDownList->AddOption(FString("Fullscreen"));
}

void UDisplayModeSetting::SetSelectedOption(UComboBoxString* DropDownList)
{
	switch (DisplayMode)
	{
	case EWindowMode::Windowed:
		SelectedOption = "Windowed";
		DropDownList->SetSelectedOption(SelectedOption);
	break;

	case EWindowMode::WindowedFullscreen:
		SelectedOption = "Windowed Fullscreen";
		DropDownList->SetSelectedOption(SelectedOption);
	break;

	case EWindowMode::Fullscreen:
		SelectedOption = "Fullscreen";
		DropDownList->SetSelectedOption(SelectedOption);
	break;

	default:
	break;
	}
}

void UDisplayModeSetting::ChangeDisplayMode(const FString& SelectedItem)
{
	if (!bInitialized)
		return;

	SelectedOption = SelectedItem;

	if (SelectedItem == "Windowed")
	{
		DisplayMode = EWindowMode::Windowed;
	}
	else if (SelectedItem == "Windowed Fullscreen")
	{
		DisplayMode = EWindowMode::WindowedFullscreen;
	}
	else if (SelectedItem == "Fullscreen")
	{
		DisplayMode = EWindowMode::Fullscreen;
	}
}

void UDisplayModeSetting::Init()
{
	Super::Init();

	AppliedDisplayMode = DisplayMode;

	DropDownList = Cast<UComboBoxString>(WidgetTree->FindWidget(FName("DropDown")));
	SetSelectedOption(DropDownList);

	bInitialized = true;
}

void UDisplayModeSetting::Apply()
{
	Super::Apply();

	AppliedDisplayMode = DisplayMode;

	GameUserSettings->SetFullscreenMode(DisplayMode);

	SaveConfig(CPF_Config, *GGameUserSettingsIni);
}

void UDisplayModeSetting::Reset()
{
	DisplayMode = DefaultDisplayMode;
	AppliedDisplayMode = DisplayMode;
	SelectedOption = DefaultOption;
	AppliedChange = SelectedOption;

	ChangeDisplayMode(SelectedOption);
	SetSelectedOption(DropDownList);
}

bool UDisplayModeSetting::IsAffectedByReset()
{
	return false;
}

bool UDisplayModeSetting::HasChanged()
{
	if (DisplayMode == AppliedDisplayMode)
		return false;
	
	return true;
}

void UDisplayModeSetting::RevertChange()
{
	ChangeDisplayMode(AppliedChange);
	SetSelectedOption(DropDownList);
}
