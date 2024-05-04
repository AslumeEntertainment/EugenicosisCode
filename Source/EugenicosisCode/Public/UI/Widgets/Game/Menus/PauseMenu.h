// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Headers/UI/ButtonDelegates.h"
#include "PauseMenu.generated.h"

class UButton;

UCLASS()
class EUGENICOSISCODE_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UFUNCTION()
	void OnOptionsClicked();

	UFUNCTION()
	void OnMainMenuClicked();

	UFUNCTION()
	void OnExitClicked();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* BTN_Options;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* BTN_MainMenu;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* BTN_Exit;

public:

	virtual void NativeOnInitialized() override;
	
	UFUNCTION(BlueprintNativeEvent)
	void CloseMenu();

	FButtonClicked OptionsClicked;
	FButtonClicked MainMenuClicked;
	FButtonClicked ExitClicked;

};
