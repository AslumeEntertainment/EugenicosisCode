// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Game/GameProgressTreeWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "UI/Widgets/Game/GameProgressEntryIcon.h"


void UGameProgressTreeWidget::AddIconToCanvas(UWidget* Icon, FVector2D Position)
{
	Canvas->AddChildToCanvas(Icon);

	UCanvasPanelSlot* PanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(Icon);
	if (!PanelSlot)
	{
		return;
	}

	PanelSlot->SetAutoSize(true);
	PanelSlot->SetPosition(Position);
}

void UGameProgressTreeWidget::ConnectIcons(UWidget* FirstIcon, UWidget* SecondIcon)
{
	FVector2D FirstCenterPosition, SecondCenterPosition;

	UCanvasPanelSlot* FirstPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(FirstIcon);
	if (!FirstPanelSlot)
	{
		return; 
	}

	FirstCenterPosition = FirstPanelSlot->GetPosition() + GetRootIconSize() / 2;

	UCanvasPanelSlot* SecondPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(SecondIcon);
	if (!SecondPanelSlot)
	{
		return;
	}

	SecondCenterPosition = SecondPanelSlot->GetPosition() + GetRootIconSize() / 2;

	FVector2D DifferenceVector = SecondCenterPosition - FirstCenterPosition;

	UUserWidget* Line = CreateWidget<UUserWidget>(UGameplayStatics::GetGameInstance(GetWorld()), ConnectingLineWidgetClass);
	Line->SetRenderShear(FVector2D(0, UKismetMathLibrary::DegAtan2(DifferenceVector.Y, DifferenceVector.X)));

	Canvas->AddChildToCanvas(Line);
	
	UCanvasPanelSlot* LinePanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(Line);
	if (!LinePanelSlot)  
	{
		return;
	}
	LinePanelSlot->SetAutoSize(true);

	FVector2D LinePosition = (FirstCenterPosition + SecondCenterPosition) / 2;
	LinePosition -= GetConnectingLineSize() / 2;

	LinePanelSlot->SetPosition(LinePosition);
	LinePanelSlot->SetZOrder(-1);
}

FVector2D UGameProgressTreeWidget::GetRootIconPosition()
{
	UCanvasPanelSlot* PanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(RootIcon);
	if (PanelSlot)
	{
		return PanelSlot->GetPosition();
	}

	return FVector2D();
}

FVector2D UGameProgressTreeWidget::GetRootIconSize()
{
	UCanvasPanelSlot* PanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(RootIcon);
	if (PanelSlot)
	{
		return PanelSlot->GetSize();
	}

	return FVector2D();
}

FVector2D UGameProgressTreeWidget::GetConnectingLineSize()
{
	UCanvasPanelSlot* PanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(Canvas->GetAllChildren()[1]);
	if (PanelSlot)
	{
		return PanelSlot->GetSize();
	}

	return FVector2D();
}

TArray<UWidget*> UGameProgressTreeWidget::GetEntryIcons()
{
	TArray<UWidget*> Icons;
	for (UWidget* Child : Canvas->GetAllChildren())
	{
		if (UGameplayStatics::GetObjectClass(Child) == UGameplayStatics::GetObjectClass(RootIcon))
		{
			Icons.Add(Child);
		}
	}

	return Icons;
}

UClass* UGameProgressTreeWidget::GetIconClass()
{
	return UGameplayStatics::GetObjectClass(RootIcon);
}

UClass* UGameProgressTreeWidget::GetConnectingLineWidgetClass()
{
	return ConnectingLineWidgetClass;
}
