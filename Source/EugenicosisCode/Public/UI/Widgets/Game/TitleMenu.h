// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Headers/UI/ButtonDelegates.h"
#include "TitleMenu.generated.h"

class UButton;

UCLASS()
class EUGENICOSISCODE_API UTitleMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UFUNCTION()
	void OnContinueClicked();

	UFUNCTION()
	void OnNewGameClicked();

	UFUNCTION()
	void OnOptionsClicked();

	UFUNCTION()
	void OnQuitClicked();
		
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* BTN_Continue;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* BTN_NewGame;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* BTN_Options;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* BTN_Quit;

public:
	virtual void NativeOnInitialized() override;

	FButtonClicked ContinueClicked;
	FButtonClicked NewGameClicked;
	FButtonClicked OptionsClicked;
	FButtonClicked QuitClicked;
};
