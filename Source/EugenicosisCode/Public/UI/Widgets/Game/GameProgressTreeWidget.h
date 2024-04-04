// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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

public:

	void AddIconToCanvas(UWidget* Icon, FVector2D Position);
	void ConnectIcons(UWidget* FirstIcon, UWidget* SecondIcon);

	FVector2D GetRootIconPosition();
	FVector2D GetRootIconSize();
	FVector2D GetConnectingLineSize();

	TArray<UWidget*> GetEntryIcons();

	UClass* GetIconClass();
	UClass* GetConnectingLineWidgetClass();
};
