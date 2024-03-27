// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TitleHUD.generated.h"

class UTitleMenu;
class UGameProgressMenu;
class UGameProgressInfoWidget;
class USettingsMenu;

UCLASS()
class EUGENICOSISCODE_API ATitleHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UTitleMenu> TitleMenuClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameProgressMenu> GameProgressMenuClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameProgressInfoWidget> GameProgressInfoWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<USettingsMenu> SettingsMenuClass;

	UPROPERTY()
	UTitleMenu* TitleMenu;

	UPROPERTY() 
	UGameProgressMenu* GameProgressMenu;

	UPROPERTY()
	UGameProgressInfoWidget* GameProgressInfoWidget;

	UPROPERTY()
	USettingsMenu* SettingsMenu;

	void ClearWidgets();

	UFUNCTION()
	void ShowTitleMenu();

	UFUNCTION()
	void ShowGameProgressMenu();

	UFUNCTION()
	void ShowGameProgressInfoWidget();

	UFUNCTION()
	void ShowSettingsMenu();
	
};
