// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InGameHUD.generated.h"

class UOverlayWidgetBase;

UCLASS()
class EUGENICOSISCODE_API AInGameHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetBase> OverlayWidgetClass;

	UPROPERTY()
	UOverlayWidgetBase* OverlayWidget;

	void ClearWidgets();

	void ShowOverlayWidget();

public:

	UFUNCTION()
	void SetOverlayBlur(float Percentage);

};



