// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InGameHUD.generated.h"

class UOverlayWidgetBase;
class UPauseMenuWidget;

UCLASS()
class EUGENICOSISCODE_API AInGameHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetBase> OverlayWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UPauseMenuWidget> PauseMenuWidgetClass;

	UPROPERTY()
	UOverlayWidgetBase* OverlayWidget;

	UPROPERTY()
	UPauseMenuWidget* PauseMenuWidget;

	void ClearWidgets();

	void ShowOverlayWidget();

	UFUNCTION()
	void ShowPauseMenu();

public:

	UFUNCTION()
	void SetOverlayBlur(float Percentage);

	UFUNCTION()
	void TogglePauseMenu(bool bIsPaused);

};



