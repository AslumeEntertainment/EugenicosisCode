// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Game/GameProgressTreeWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"
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

	//PanelSlot->SetAnchors(FAnchors(800, 450));
	//PanelSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
	//PanelSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);

	PanelSlot->SetPosition(Position);
}

FVector2D UGameProgressTreeWidget::GetRootIconPosition()
{
	UCanvasPanelSlot* PanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(RootIcon);
	if (PanelSlot)
	{
		return PanelSlot->GetPosition();
	}

	return FVector2D(0, 0);
}

TArray<UWidget*> UGameProgressTreeWidget::GetEntryIcons()
{
	return Canvas->GetAllChildren();
}

UClass* UGameProgressTreeWidget::GetIconClass()
{
	return UGameplayStatics::GetObjectClass(RootIcon);
}
