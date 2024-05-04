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

	UFUNCTION(BlueprintNativeEvent)
	void CloseInfo();

	void SetTitle(FText Title);
	void SetDescription(FText Description);
	
	FText GetTitle();

	FButtonClicked BeforeCutsceneClicked;
	FButtonClicked AfterCutsceneClicked;

};
