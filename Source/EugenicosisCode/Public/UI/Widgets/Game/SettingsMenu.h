// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ButtonDelegates.h"
#include "SettingsMenu.generated.h"

class UButton;

UCLASS()
class EUGENICOSISCODE_API USettingsMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UFUNCTION()
	void OnBackClicked();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* BTN_Back;

public:

	virtual void NativeOnInitialized() override;

	FButtonClicked BackClicked;
};
