// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Game/GameProgressWidgets/GameProgressTreeWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

#include "UI/Widgets/Game/GameProgressWidgets/GameProgressEntryIcon.h"
#include "Headers/UI/DragWidget.h"


FReply UGameProgressTreeWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	FEventReply ReplyResult = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	return ReplyResult.NativeReply;
}

void UGameProgressTreeWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UDragWidget* DragDropOperation = NewObject<UDragWidget>();
	this->SetVisibility(ESlateVisibility::HitTestInvisible);

	DragDropOperation->ReferenceWidget = this;
	DragDropOperation->DragOffset = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
	DragDropOperation->DefaultDragVisual = this;
	DragDropOperation->Pivot = EDragPivot::MouseDown;

	OutOperation = DragDropOperation;
	OnBackgroundPressed.Broadcast();
}

void UGameProgressTreeWidget::NativeOnDragLeave(const FDragDropEvent& DragDropEvent, UDragDropOperation* InOperation)
{
	UDragWidget* DragWidgetResult = Cast<UDragWidget>(InOperation);
	if (!IsValid(DragWidgetResult))
	{
		UE_LOG(LogTemp, Warning, TEXT("UGameProgressTreeWidget::NativeOnDragLeave DragWidgetResult == nullptr"))
		return;
	}

	UCanvasPanelSlot* PanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(this);
	if (!PanelSlot)
	{
		UE_LOG(LogTemp, Warning, TEXT("UGameProgressTreeWidget::NativeOnDragLeave PanelSlot == nullptr"))
		return;
	}

	DragWidgetResult->WidgetSize = PanelSlot->GetSize();
	DragWidgetResult->StartingPosition = PanelSlot->GetPosition();
	DragWidgetResult->ParentWidget = GetParent();

	RemoveFromParent();
}

void UGameProgressTreeWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UDragWidget* DragWidgetResult = Cast<UDragWidget>(InOperation);
	if (!IsValid(DragWidgetResult))
	{
		UE_LOG(LogTemp, Warning, TEXT("UGameProgressTreeWidget::NativeOnDragLeave DragWidgetResult == nullptr"))
		return;
	}

	DragWidgetResult->ReferenceWidget->AddToViewport();
	DragWidgetResult->ReferenceWidget->SetVisibility(ESlateVisibility::Visible);

	UCanvasPanel* ParentCanvas = Cast<UCanvasPanel>(DragWidgetResult->ParentWidget);
	if (!IsValid(ParentCanvas))
	{
		UE_LOG(LogTemp, Warning, TEXT("UGameProgressTreeWidget::NativeOnDragLeave ParentCanvas == nullptr"))
		return;
	}
	ParentCanvas->AddChildToCanvas(DragWidgetResult->ReferenceWidget);

	UCanvasPanelSlot* PanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(DragWidgetResult->ReferenceWidget);
	if (!PanelSlot)
	{
		UE_LOG(LogTemp, Warning, TEXT("UGameProgressTreeWidget::NativeOnDragLeave PanelSlot == nullptr"))
		return;
	}
	PanelSlot->SetPosition(DragWidgetResult->StartingPosition);
	PanelSlot->SetSize(DragWidgetResult->WidgetSize);

	UE_LOG(LogTemp, Warning, TEXT("Trying to drag the Progress Tree Widget outside the game viewport!"));
}

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
	if (!PanelSlot)
	{
		return FVector2D();
	}

	return PanelSlot->GetPosition();
}

FVector2D UGameProgressTreeWidget::GetRootIconSize()
{
	UCanvasPanelSlot* PanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(RootIcon);
	if (!PanelSlot)
	{
		return FVector2D();
	}

	return PanelSlot->GetSize();
}

FVector2D UGameProgressTreeWidget::GetConnectingLineSize()
{
	UCanvasPanelSlot* PanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(Canvas->GetAllChildren()[1]);
	if (!PanelSlot)
	{
		UE_LOG(LogTemp, Warning, TEXT("UGameProgressTreeWidget::GetConnectingLineSize Invalid Line Widget"))
		return FVector2D();
	}

	return PanelSlot->GetSize();
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
