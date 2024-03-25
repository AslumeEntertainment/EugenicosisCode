// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InGameHUD.generated.h"

class UOverlayWidgetBase;
class UPauseMenu;
class USettingsMenu;

UCLASS()
class EUGENICOSISCODE_API AInGameHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetBase> OverlayWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UPauseMenu> PauseMenuClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<USettingsMenu> SettingsMenuClass;

	UPROPERTY()
	UOverlayWidgetBase* OverlayWidget;

	UPROPERTY()
	UPauseMenu* PauseMenu;

	UPROPERTY()
	USettingsMenu* SettingsMenu;

	void ClearWidgets();

	void ShowOverlayWidget();

	UFUNCTION()
	void ShowPauseMenu();

	UFUNCTION()
	void ShowSettingsMenu();

public:

	UFUNCTION()
	void SetOverlayBlur(float Percentage);

	UFUNCTION()
	void TogglePauseMenu(bool bIsPaused);

};



