// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "DragWidget.generated.h"


UCLASS()
class EUGENICOSISCODE_API UDragWidget : public UDragDropOperation
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	UUserWidget* ReferenceWidget;

	UPROPERTY(EditAnywhere)
	FVector2D DragOffset;
};
