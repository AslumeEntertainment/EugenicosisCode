// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Headers/UI/ButtonDelegates.h"
#include "GameProgressMenu.generated.h"

class UCanvasPanel;
class UGameProgressEntryIcon;
class UGameProgressTreeWidget;

UCLASS()
class EUGENICOSISCODE_API UGameProgressMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UFUNCTION()
	void OnBackClicked();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UCanvasPanel* Canvas;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UGameProgressTreeWidget* GameProgressTree;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* BTN_Back;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeConstruct() override;

public:

	virtual void NativeOnInitialized() override;

	void DrawTreeLevel(TArray<struct FGameProgressDataStruct*> GameProgressData, int Level);
	void DrawTreeLines(TArray<struct FGameProgressDataStruct*> GameProgressData);

	TArray<UWidget*> GetEntryIcons();
	UGameProgressTreeWidget* GetProgressTree();

	FButtonClicked BackClicked;
};
