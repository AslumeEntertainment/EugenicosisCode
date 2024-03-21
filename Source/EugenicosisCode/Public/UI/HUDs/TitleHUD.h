// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TitleHUD.generated.h"

class UTitleMenu;

UCLASS()
class EUGENICOSISCODE_API ATitleHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UTitleMenu> TitleMenuWidgetClass;

	UPROPERTY()
	UTitleMenu* TitleMenuWidget;

	void ClearWidgets();

	UFUNCTION()
	void ShowTitleMenu();
	
};
