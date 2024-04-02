// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Headers/UI/ButtonDelegates.h"
#include "GameProgressInfoWidget.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class EUGENICOSISCODE_API UGameProgressInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UFUNCTION()
	void OnBeforeCutsceneClicked();

	UFUNCTION()
	void OnAfterCutsceneClicked();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* BTN_StartBeforeCutscene;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* BTN_StartAfterCutscene;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* TXT_Title;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* TXT_Description;

public:

	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void SetTitle(FText Title);

	UFUNCTION()
	void SetDescription(FText Description);

	FButtonClicked BeforeCutsceneClicked;
	FButtonClicked AfterCutsceneClicked;

};
