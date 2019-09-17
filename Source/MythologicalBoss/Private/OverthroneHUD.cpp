// Copyright Overthrone Studios 2019

#include "Public/OverthroneHUD.h"

#include "Widgets/HUD/MasterHUD.h"
#include "Widgets/HUD/MainPlayerHUD.h"

#include "Widget.h"
#include "WidgetTree.h"
#include "UserWidget.h"

#include "ConstructorHelpers.h"
#include "Log.h"
#include "Engine/Engine.h"

AOverthroneHUD::AOverthroneHUD()
{
	static ConstructorHelpers::FClassFinder<UWidget> MasterHUDWidget(TEXT("WidgetBlueprint'/Game/UI/PlayerHUD/UI_MasterPlayerHUD.UI_MasterPlayerHUD_C'"));

	if (MasterHUDWidget.Succeeded())
		HUDWidgetClass = MasterHUDWidget.Class;
}

void AOverthroneHUD::Init()
{
	CreateWidgets();

	if (MasterHUD)
	{
		AddWidgetsToScreen();
		InitWidgets();
	}
	else
	{
		ULog::DebugMessage(ERROR, FString("Failed to create the MasterHUD widget!"), true);
	}
}

UMainPlayerHUD* AOverthroneHUD::GetMainHUD() const
{
	return Cast <UMainPlayerHUD>(MasterHUD->GetHUD("MainHUD"));
}

void AOverthroneHUD::AddOnScreenDebugMessage(const FString& Message, const FLinearColor Color, const float YPadding)
{
	FDebugData DebugData;

	DebugData.Message = Message;
	DebugData.Color = Color;
	DebugData.XOffset = BaseXOffset;
	DebugData.YOffset = NewYOffset + YPadding;

	DebugMessages.Add(DebugData);

	NewYOffset += YOffsetInterval;
}

void AOverthroneHUD::UpdateOnScreenDebugMessage(const int32 Index, const FString& Message)
{
	if (DebugMessages.IsValidIndex(Index))
		DebugMessages[Index].Message = Message;
}

void AOverthroneHUD::DrawHUD()
{
	if (bHideDebugText && !HasActorBegunPlay())
		return;

	GEngine->GameViewport->GetViewportSize(ViewportSize);

	for (const FDebugData& Debug : DebugMessages)
	{
		DrawText(Debug.Message, Debug.Color, ViewportSize.X - Debug.XOffset, Debug.YOffset);
	}
}

void AOverthroneHUD::CreateWidgets()
{
	MasterHUD = CreateWidget<UMasterHUD>(GetWorld(), HUDWidgetClass, FName("Master Player HUD"));
}

void AOverthroneHUD::AddWidgetsToScreen()
{
	MasterHUD->AddToViewport();
	MasterHUD->SetVisibility(ESlateVisibility::Visible);
}

void AOverthroneHUD::InitWidgets()
{
	MasterHUD->Init();

#if !UE_BUILD_SHIPPING
	MasterHUD->SwitchToHUDIndex(0);
#else
	MasterHUD->SwitchToHUDIndex(2);
	MasterHUD->HideTitle();
	MasterHUD->HideBoxes();
#endif
}
