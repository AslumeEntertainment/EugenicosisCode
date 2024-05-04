// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUDs/InGameHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#include "Gamemodes/EGC_GameModeBase.h"
#include "UI/Widgets/Game/OverlayWidgetBase.h"
#include "UI/Widgets/Game/Menus/PauseMenu.h"
#include "UI/Widgets/Game/Menus/SettingsMenu.h"

void AInGameHUD::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerOwner)
	{
		PlayerOwner->SetInputMode(FInputModeGameOnly());
		PlayerOwner->bShowMouseCursor = false;
	}

	AEGC_GameModeBase* GameMode = Cast<AEGC_GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!IsValid(GameMode))
	{
		UE_LOG(LogTemp, Error, TEXT("AInGameHUD::BeginPlay IsValid(GameMode) == false"));
		return;
	}

	OverlayWidget = CreateWidget<UOverlayWidgetBase>(UGameplayStatics::GetGameInstance(GetWorld()), OverlayWidgetClass);
	PauseMenu = CreateWidget<UPauseMenu>(UGameplayStatics::GetGameInstance(GetWorld()), PauseMenuClass);
	SettingsMenu = CreateWidget<USettingsMenu>(UGameplayStatics::GetGameInstance(GetWorld()), SettingsMenuClass);

	PauseMenu->OptionsClicked.AddDynamic(this, &AInGameHUD::ShowSettingsMenu);
	PauseMenu->MainMenuClicked.AddDynamic(GameMode, &AEGC_GameModeBase::ReturnToTitle);
	PauseMenu->ExitClicked.AddDynamic(GameMode, &AEGC_GameModeBase::QuitGame);

	SettingsMenu->BackClicked.AddDynamic(this, &AInGameHUD::ShowPauseMenu);

	ShowOverlayWidget();
}

void AInGameHUD::ClearWidgets()
{
	if (PlayerOwner) 
	{
		PlayerOwner->SetInputMode(FInputModeGameOnly());
		PlayerOwner->bShowMouseCursor = false;
	}

	UWidgetLayoutLibrary::RemoveAllWidgets(this);
	ShowOverlayWidget();
}

void AInGameHUD::ShowOverlayWidget()
{
	if (!PlayerOwner || !OverlayWidget) 
	{
		return;
	}

	OverlayWidget->AddToViewport();
	PlayerOwner->bShowMouseCursor = false;
	PlayerOwner->SetInputMode(FInputModeGameOnly());
}

void AInGameHUD::ShowPauseMenu()
{
	ClearWidgets();

	if (!PlayerOwner || !PauseMenu) 
	{
		return;
	}

	PauseMenu->AddToViewport();
	PlayerOwner->SetInputMode(FInputModeGameAndUI());
	PlayerOwner->bShowMouseCursor = true;
}

void AInGameHUD::ShowSettingsMenu()
{
	ClearWidgets();

	if (!PlayerOwner || !SettingsMenu)
	{
		return;
	}

	SettingsMenu->AddToViewport();
	PlayerOwner->SetInputMode(FInputModeUIOnly());
	PlayerOwner->bShowMouseCursor = true;
}

void AInGameHUD::SetOverlayBlur(float Percentage)
{
	OverlayWidget->SetBlur(Percentage);
	OverlayWidget->SetShading(Percentage);
}

void AInGameHUD::TogglePauseMenu(bool bIsPaused)
{
	if (!PlayerOwner)
	{
		return;
	}

	if (bIsPaused)
	{
		ShowPauseMenu();
	}
	else
	{
		PauseMenu->CloseMenu();
		PlayerOwner->SetInputMode(FInputModeGameOnly());
		PlayerOwner->bShowMouseCursor = false;
	}
}

