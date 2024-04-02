// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Headers/UI/ButtonDelegates.h"
#include "GameProgressEntryIcon.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class EUGENICOSISCODE_API UGameProgressEntryIcon : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UFUNCTION()
	void OnIconClicked();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* BTN_Icon;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* TXT_EntryName;

public:

	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void SetEntryName(FText EntryName);

	FButtonClicked IconClicked;
};
