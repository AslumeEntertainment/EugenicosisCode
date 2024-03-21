// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUDs/TitleHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#include "Gamemodes/EGC_TitleGameMode.h"
#include "UI/Widgets/Game/TitleMenu.h"

void ATitleHUD::BeginPlay()
{
	Super::BeginPlay();

	AEGC_TitleGameMode* GameMode = Cast<AEGC_TitleGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!IsValid(GameMode)) {
		return;
	}

	PlayerOwner->SetInputMode(FInputModeUIOnly());
	PlayerOwner->bShowMouseCursor = true;

	TitleMenuWidget = CreateWidget<UTitleMenu>(UGameplayStatics::GetGameInstance(GetWorld()), TitleMenuWidgetClass);

	TitleMenuWidget->QuitClicked.AddDynamic(GameMode, &AEGC_TitleGameMode::QuitGame);

	ShowTitleMenu();
}

void ATitleHUD::ClearWidgets()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
}

void ATitleHUD::ShowTitleMenu()
{
	ClearWidgets();

	if (PlayerOwner && TitleMenuWidget)
	{
		TitleMenuWidget->AddToViewport();
	}
}
