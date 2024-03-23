// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Game/PauseMenuWidget.h"

#include "Components/Button.h"

void UPauseMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	BTN_Options->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnOptionsClicked);
	BTN_MainMenu->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnMainMenuClicked);
	BTN_Exit->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnExitClicked);
}

void UPauseMenuWidget::OnOptionsClicked()
{
	OptionsClicked.Broadcast();
}

void UPauseMenuWidget::OnMainMenuClicked()
{
	MainMenuClicked.Broadcast();
}

void UPauseMenuWidget::OnExitClicked()
{
	ExitClicked.Broadcast();
}

