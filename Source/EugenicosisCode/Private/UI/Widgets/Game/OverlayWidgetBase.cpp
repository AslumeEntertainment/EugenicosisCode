// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Game/OverlayWidgetBase.h"

#include "Components/BackgroundBlur.h"
#include "Components/Border.h"

void UOverlayWidgetBase::SetBlur(float Percentage)
{
	BackgroundBlur->SetBlurStrength(MaxBlurValue * (1 - Percentage));
}

void UOverlayWidgetBase::SetShading(float Percentage)
{
	FLinearColor Color = BackgroundShading->GetBrushColor();
	BackgroundShading->SetBrushColor(FLinearColor(Color.R, Color.B, Color.G, MaxShadingValue * (1 - Percentage)));
}