// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Game/PauseMenu.h"

#include "Components/Button.h"

void UPauseMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	BTN_Options->OnClicked.AddDynamic(this, &UPauseMenu::OnOptionsClicked);
	BTN_MainMenu->OnClicked.AddDynamic(this, &UPauseMenu::OnMainMenuClicked);
	BTN_Exit->OnClicked.AddDynamic(this, &UPauseMenu::OnExitClicked);
}

void UPauseMenu::OnOptionsClicked()
{
	OptionsClicked.Broadcast();
}

void UPauseMenu::OnMainMenuClicked()
{
	MainMenuClicked.Broadcast();
}

void UPauseMenu::OnExitClicked()
{
	ExitClicked.Broadcast();
}

