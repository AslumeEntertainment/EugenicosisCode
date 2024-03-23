// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUDs/InGameHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#include "UI/Widgets/Game/OverlayWidgetBase.h"
#include "UI/Widgets/Game/PauseMenuWidget.h"

void AInGameHUD::BeginPlay()
{
	if (PlayerOwner) 
	{
		PlayerOwner->SetInputMode(FInputModeGameOnly());
		PlayerOwner->bShowMouseCursor = false;
	}

	Super::BeginPlay();

	OverlayWidget = CreateWidget<UOverlayWidgetBase>(UGameplayStatics::GetGameInstance(GetWorld()), OverlayWidgetClass);
	PauseMenuWidget = CreateWidget<UPauseMenuWidget>(UGameplayStatics::GetGameInstance(GetWorld()), PauseMenuWidgetClass);

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
	PlayerOwner->SetPause(false);
	PlayerOwner->bShowMouseCursor = false;
	PlayerOwner->SetInputMode(FInputModeGameOnly());
}

void AInGameHUD::ShowPauseMenu()
{
	ClearWidgets();

	if (PlayerOwner) 
	{
		PauseMenuWidget->AddToViewport();
		PlayerOwner->SetPause(true);
		PlayerOwner->SetInputMode(FInputModeGameAndUI());
		PlayerOwner->bShowMouseCursor = true;
	}
}

void AInGameHUD::SetOverlayBlur(float Percentage)
{
	OverlayWidget->SetBlur(Percentage);
	OverlayWidget->SetShading(Percentage);
}

void AInGameHUD::TogglePauseMenu(bool bIsPaused)
{
	if (bIsPaused)
	{
		ShowPauseMenu();
	}
	else
	{
		ClearWidgets();
	}
}

