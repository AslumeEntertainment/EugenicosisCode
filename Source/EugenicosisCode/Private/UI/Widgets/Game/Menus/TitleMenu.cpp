// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Game/Menus/TitleMenu.h"

#include "Components/Button.h"

void UTitleMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	BTN_Continue->OnClicked.AddDynamic(this, &UTitleMenu::OnContinueClicked);
	BTN_NewGame->OnClicked.AddDynamic(this, &UTitleMenu::OnNewGameClicked);
	BTN_Options->OnClicked.AddDynamic(this, &UTitleMenu::OnOptionsClicked);
	BTN_Quit->OnClicked.AddDynamic(this, &UTitleMenu::OnQuitClicked);
}

void UTitleMenu::OnContinueClicked()
{
	ContinueClicked.Broadcast();
}

void UTitleMenu::OnNewGameClicked()
{
	NewGameClicked.Broadcast();
}

void UTitleMenu::OnOptionsClicked()
{
	OptionsClicked.Broadcast();
}

void UTitleMenu::OnQuitClicked()
{
	QuitClicked.Broadcast();
}

