// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OverlayWidgetBase.generated.h"

class UBackgroundBlur;
class UBorder;

UCLASS()
class EUGENICOSISCODE_API UOverlayWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UBackgroundBlur* BackgroundBlur;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UBorder* BackgroundShading;

	UPROPERTY(EditAnywhere)
	int MaxBlurValue = 15;

	UPROPERTY(EditAnywhere)
	float MaxShadingValue = 0.2;

public:

	void SetBlur(float Percentage);
	void SetShading(float Percentage);
};
