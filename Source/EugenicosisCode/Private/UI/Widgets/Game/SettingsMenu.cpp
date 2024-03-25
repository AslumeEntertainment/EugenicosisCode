// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Game/SettingsMenu.h"

#include "Components/Button.h"

void USettingsMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	BTN_Back->OnClicked.AddDynamic(this, &USettingsMenu::OnBackClicked);
}

void USettingsMenu::OnBackClicked()
{
	BackClicked.Broadcast();
}
