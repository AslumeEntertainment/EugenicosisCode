// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUDs/InGameHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#include "UI/Widgets/Game/OverlayWidgetBase.h"

void AInGameHUD::BeginPlay()
{
	Super::BeginPlay();

	OverlayWidget = CreateWidget<UOverlayWidgetBase>(UGameplayStatics::GetGameInstance(GetWorld()), OverlayWidgetClass);

	ShowOverlayWidget();
}

void AInGameHUD::ClearWidgets()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
}

void AInGameHUD::ShowOverlayWidget()
{
	//ClearWidgets();

	if (!PlayerOwner || !OverlayWidget) {
		return;
	}

	OverlayWidget->AddToViewport();
	PlayerOwner->SetPause(false);
	PlayerOwner->bShowMouseCursor = false;
	PlayerOwner->SetInputMode(FInputModeGameOnly());
}

void AInGameHUD::SetOverlayBlur(float Percentage)
{
	OverlayWidget->SetBlur(Percentage);
	OverlayWidget->SetShading(Percentage);
}

