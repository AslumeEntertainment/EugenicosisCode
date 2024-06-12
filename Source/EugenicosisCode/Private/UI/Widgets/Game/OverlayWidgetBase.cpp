// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Game/OverlayWidgetBase.h"

#include "Components/BackgroundBlur.h"
#include "Components/Border.h"
#include "Components/ProgressBar.h"

void UOverlayWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
	VolumeMeter->SetPercent(0);
}

void UOverlayWidgetBase::SetBlur(float Percentage)
{
	BackgroundBlur->SetBlurStrength(MaxBlurValue * (1 - Percentage));
}

void UOverlayWidgetBase::SetShading(float Percentage)
{
	FLinearColor Color = BackgroundShading->GetBrushColor();
	BackgroundShading->SetBrushColor(FLinearColor(Color.R, Color.B, Color.G, MaxShadingValue * (1 - Percentage)));
}

void UOverlayWidgetBase::SetVolumeLevel(float Percentage)
{
	GEngine->AddOnScreenDebugMessage(101, 1, FColor::Cyan, FString::Printf(TEXT("Volume: %f"), Percentage));
	VolumeMeter->SetPercent(Percentage);
}
