// Copyright Ali El Saleh 2019

#pragma once

#include "Widgets/Menus/MenuBase.h"
#include "ControlsMenu.generated.h"

/**
 * A controls menu is where you can change the controls of the game
 */
UCLASS()
class MENUSYSTEM_API UControlsMenu final : public UMenuBase
{
	GENERATED_BODY()
	
public:
	void ResetKeyBindings();

	void Init() override;

	void Back() override;
	void GoBack() override;

protected:
	UPROPERTY(BlueprintReadWrite)
		TArray<UUserWidget*> ControlsSlots;
};
