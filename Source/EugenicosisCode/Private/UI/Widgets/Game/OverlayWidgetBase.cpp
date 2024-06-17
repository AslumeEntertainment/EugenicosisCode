// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Game/OverlayWidgetBase.h"

#include "Components/BackgroundBlur.h"
#include "Components/Border.h"
#include "Components/ProgressBar.h"

void UOverlayWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
	ResetVolumeLevel();
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

void UOverlayWidgetBase::SetVolumeLevel(float Percentage, float HorizontalDirectionValue, float VerticalDirectionValue)
{
	GEngine->AddOnScreenDebugMessage(101, 1, FColor::Cyan, FString::Printf(TEXT("Displayed Volume: %f"), Percentage));

	VolumeMeter->SetPercent(Percentage);

	UMaterialInstanceDynamic* FullVisualSoundBorderMaterial = VisualSoundBorder_Full->GetDynamicMaterial();
	if (!FullVisualSoundBorderMaterial)
	{
		UE_LOG(LogTemp, Error, TEXT("UOverlayWidgetBase::SetVolumeLevel FullVisualSoundBorderMaterial == nullptr"));
		return;
	}

	UMaterialInstanceDynamic* DownVisualSoundBorderMaterial = VisualSoundBorder_Down->GetDynamicMaterial();
	if (!DownVisualSoundBorderMaterial)
	{
		UE_LOG(LogTemp, Error, TEXT("UOverlayWidgetBase::SetVolumeLevel DownVisualSoundBorderMaterial == nullptr"));
		return;
	}

	UMaterialInstanceDynamic* RightVisualSoundBorderMaterial = VisualSoundBorder_Right->GetDynamicMaterial();
	if (!RightVisualSoundBorderMaterial)
	{
		UE_LOG(LogTemp, Error, TEXT("UOverlayWidgetBase::SetVolumeLevel RightVisualSoundBorderMaterial == nullptr"));
		return;
	}

	UMaterialInstanceDynamic* UpVisualSoundBorderMaterial = VisualSoundBorder_Up->GetDynamicMaterial();
	if (!UpVisualSoundBorderMaterial)
	{
		UE_LOG(LogTemp, Error, TEXT("UOverlayWidgetBase::SetVolumeLevel UpVisualSoundBorderMaterial == nullptr"));
		return;
	}

	UMaterialInstanceDynamic* LeftVisualSoundBorderMaterial = VisualSoundBorder_Left->GetDynamicMaterial();
	if (!LeftVisualSoundBorderMaterial)
	{
		UE_LOG(LogTemp, Error, TEXT("UOverlayWidgetBase::SetVolumeLevel LeftVisualSoundBorderMaterial == nullptr"));
		return;
	}

	if (FMath::Abs(HorizontalDirectionValue) < 0.25)
	{
		LeftVisualSoundBorderMaterial->SetScalarParameterValue("Strength", Percentage/5);
		RightVisualSoundBorderMaterial->SetScalarParameterValue("Strength", Percentage / 5);
	}
	else if (HorizontalDirectionValue > 0)
	{
		LeftVisualSoundBorderMaterial->SetScalarParameterValue("Strength", 0);
		RightVisualSoundBorderMaterial->SetScalarParameterValue("Strength", Percentage / 5);
	}
	else
	{
		LeftVisualSoundBorderMaterial->SetScalarParameterValue("Strength", Percentage / 5);
		RightVisualSoundBorderMaterial->SetScalarParameterValue("Strength", 0);
	}

	if (FMath::Abs(VerticalDirectionValue) < 0.25)
	{
		UpVisualSoundBorderMaterial->SetScalarParameterValue("Strength", Percentage / 5);
		DownVisualSoundBorderMaterial->SetScalarParameterValue("Strength", Percentage / 5);
	}
	else if (VerticalDirectionValue > 0)
	{
		UpVisualSoundBorderMaterial->SetScalarParameterValue("Strength", 0);
		DownVisualSoundBorderMaterial->SetScalarParameterValue("Strength", Percentage / 5);
	}
	else
	{
		UpVisualSoundBorderMaterial->SetScalarParameterValue("Strength", Percentage / 5);
		DownVisualSoundBorderMaterial->SetScalarParameterValue("Strength", 0);
	}

	FullVisualSoundBorderMaterial->SetScalarParameterValue("Strength", Percentage / 5);
	FullVisualSoundBorderMaterial->SetScalarParameterValue("Size", Percentage / 10);
}

void UOverlayWidgetBase::ResetVolumeLevel()
{
	VolumeMeter->SetPercent(0);

	UMaterialInstanceDynamic* FullVisualSoundBorderMaterial = VisualSoundBorder_Full->GetDynamicMaterial();
	if (!FullVisualSoundBorderMaterial)
	{
		UE_LOG(LogTemp, Error, TEXT("UOverlayWidgetBase::ResetVolumeLevel FullVisualSoundBorderMaterial == nullptr"));
		return;
	}

	UMaterialInstanceDynamic* DownVisualSoundBorderMaterial = VisualSoundBorder_Down->GetDynamicMaterial();
	if (!DownVisualSoundBorderMaterial)
	{
		UE_LOG(LogTemp, Error, TEXT("UOverlayWidgetBase::SetVolumeLevel DownVisualSoundBorderMaterial == nullptr"));
		return;
	}

	UMaterialInstanceDynamic* RightVisualSoundBorderMaterial = VisualSoundBorder_Right->GetDynamicMaterial();
	if (!RightVisualSoundBorderMaterial)
	{
		UE_LOG(LogTemp, Error, TEXT("UOverlayWidgetBase::SetVolumeLevel RightVisualSoundBorderMaterial == nullptr"));
		return;
	}

	UMaterialInstanceDynamic* UpVisualSoundBorderMaterial = VisualSoundBorder_Up->GetDynamicMaterial();
	if (!UpVisualSoundBorderMaterial)
	{
		UE_LOG(LogTemp, Error, TEXT("UOverlayWidgetBase::SetVolumeLevel UpVisualSoundBorderMaterial == nullptr"));
		return;
	}

	UMaterialInstanceDynamic* LeftVisualSoundBorderMaterial = VisualSoundBorder_Left->GetDynamicMaterial();
	if (!LeftVisualSoundBorderMaterial)
	{
		UE_LOG(LogTemp, Error, TEXT("UOverlayWidgetBase::SetVolumeLevel LeftVisualSoundBorderMaterial == nullptr"));
		return;
	}

	DownVisualSoundBorderMaterial->SetScalarParameterValue("Strength", 0);
	RightVisualSoundBorderMaterial->SetScalarParameterValue("Strength", 0);
	UpVisualSoundBorderMaterial->SetScalarParameterValue("Strength", 0);
	LeftVisualSoundBorderMaterial->SetScalarParameterValue("Strength", 0);

	FullVisualSoundBorderMaterial->SetScalarParameterValue("Strength", 0);
	FullVisualSoundBorderMaterial->SetScalarParameterValue("Size", 0);
}
