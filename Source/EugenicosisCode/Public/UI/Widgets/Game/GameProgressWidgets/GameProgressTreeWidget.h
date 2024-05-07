// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Headers/UI/ButtonDelegates.h"
#include "GameProgressTreeWidget.generated.h"

class UCanvasPanel;
class UGameProgressEntryIcon;

UCLASS()
class EUGENICOSISCODE_API UGameProgressTreeWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> ConnectingLineWidgetClass;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UCanvasPanel* Canvas;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UGameProgressEntryIcon* RootIcon;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

public:

	void AddIconToCanvas(UWidget* Icon, FVector2D Position);
	void ConnectIcons(UWidget* FirstIcon, UWidget* SecondIcon);

	FVector2D GetRootIconPosition();
	FVector2D GetRootIconSize();
	FVector2D GetConnectingLineSize();

	TArray<UWidget*> GetEntryIcons();

	UClass* GetIconClass();
	UClass* GetConnectingLineWidgetClass();

	FButtonClicked OnBackgroundPressed;
};
