// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OverlayWidgetBase.generated.h"

class UBackgroundBlur;
class UBorder;
class UProgressBar;

UCLASS()
class EUGENICOSISCODE_API UOverlayWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UBackgroundBlur* BackgroundBlur;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UBorder* BackgroundShading;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UBorder* VisualSoundBorder_Full;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UBorder* VisualSoundBorder_Down;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UBorder* VisualSoundBorder_Right;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UBorder* VisualSoundBorder_Up;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UBorder* VisualSoundBorder_Left;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* VolumeMeter;

	UPROPERTY(EditAnywhere)
	int MaxBlurValue = 15;

	UPROPERTY(EditAnywhere)
	float MaxShadingValue = 0.2;

	virtual void NativeConstruct() override;

public:

	UFUNCTION()
	void SetVolumeLevel(float Percentage, float HorizontalDirectionValue, float VerticalDirectionValue);

	UFUNCTION()
	void ResetVolumeLevel();

	void SetBlur(float Percentage);
	void SetShading(float Percentage);
};
