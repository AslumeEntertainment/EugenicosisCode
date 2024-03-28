// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ButtonDelegates.h"
#include "GameProgressMenu.generated.h"

class UWrapBox;
class UGameProgressEntryIcon;

UCLASS()
class EUGENICOSISCODE_API UGameProgressMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UFUNCTION()
	void OnBackClicked();

	UFUNCTION()
	void OnBackgroundClicked();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* BTN_Back;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* BTN_Background;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UWrapBox* EntryBox;

public:

	virtual void NativeOnInitialized() override;

	void ReloadLines();

	void AddEntryIcon(UGameProgressEntryIcon* EntryIcon);

	TArray<UWidget*> GetEntryIcons();

	FButtonClicked BackClicked;
	FButtonClicked BackgroundClicked;
};
