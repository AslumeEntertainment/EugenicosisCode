// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUDs/TitleHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#include "Gamemodes/EGC_TitleGameMode.h"
#include "UI/Widgets/Game/TitleMenu.h"
#include "UI/Widgets/Game/SettingsMenu.h"

void ATitleHUD::BeginPlay()
{
	Super::BeginPlay();

	AEGC_TitleGameMode* GameMode = Cast<AEGC_TitleGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!IsValid(GameMode)) 
	{
		UE_LOG(LogTemp, Error, TEXT("ATitleHUD::BeginPlay IsValid(GameMode) == false"));
		return;
	}

	if (PlayerOwner) 
	{
		PlayerOwner->SetInputMode(FInputModeUIOnly());
		PlayerOwner->bShowMouseCursor = true;
	}

	TitleMenu = CreateWidget<UTitleMenu>(UGameplayStatics::GetGameInstance(GetWorld()), TitleMenuClass);
	SettingsMenu = CreateWidget<USettingsMenu>(UGameplayStatics::GetGameInstance(GetWorld()), SettingsMenuClass);

	TitleMenu->NewGameClicked.AddDynamic(GameMode, &AEGC_TitleGameMode::StartGame);
	TitleMenu->OptionsClicked.AddDynamic(this, &ATitleHUD::ShowSettingsMenu);
	TitleMenu->QuitClicked.AddDynamic(GameMode, &AEGC_TitleGameMode::QuitGame);

	SettingsMenu->BackClicked.AddDynamic(this, &ATitleHUD::ShowTitleMenu);

	ShowTitleMenu();
}

void ATitleHUD::ClearWidgets()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
}

void ATitleHUD::ShowTitleMenu()
{
	ClearWidgets();

	if (!PlayerOwner || !TitleMenu)
	{
		return;
	}

	TitleMenu->AddToViewport();
}

void ATitleHUD::ShowSettingsMenu()
{
	ClearWidgets();

	if (!PlayerOwner || !SettingsMenu)
	{
		return;
	}

	SettingsMenu->AddToViewport();
}
