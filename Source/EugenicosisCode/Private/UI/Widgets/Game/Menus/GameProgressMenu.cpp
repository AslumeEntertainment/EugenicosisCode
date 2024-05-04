// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Game/Menus/GameProgressMenu.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "Components/CanvasPanelSlot.h"

#include "UI/Widgets/Game/GameProgressWidgets/GameProgressEntryIcon.h"
#include "UI/Widgets/Game/GameProgressWidgets/GameProgressTreeWidget.h"
#include "Headers/UI/DragWidget.h"
#include "Headers/SaveSystem/GameProgressDataStruct.h"


bool UGameProgressMenu::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UDragWidget* DragWidgetResult = Cast<UDragWidget>(InOperation);

	if (!IsValid(DragWidgetResult))
	{
		UE_LOG(LogTemp, Warning, TEXT("UGameProgressMenu::NativeOnDrop DragWidgetResult == nullptr"))
		return false;
	}

	const FVector2D DragWindowOffset = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition());
	const FVector2D DragWindowOffsetResult = DragWindowOffset - DragWidgetResult->DragOffset;

	DragWidgetResult->ReferenceWidget->AddToViewport();
	DragWidgetResult->ReferenceWidget->SetVisibility(ESlateVisibility::Visible);
	
	Canvas->AddChildToCanvas(DragWidgetResult->ReferenceWidget);
	UCanvasPanelSlot* PanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(DragWidgetResult->ReferenceWidget);
	if (!PanelSlot)
	{
		return false;
	}
	PanelSlot->SetPosition(DragWindowOffsetResult);

	return true;
}

void UGameProgressMenu::NativeConstruct()
{
	Super::NativeConstruct();

	UCanvasPanelSlot* ProgressTreeSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(GameProgressTree);
	if (!ProgressTreeSlot)
	{
		UE_LOG(LogTemp, Warning, TEXT("UGameProgressMenu::NativeConstruct ProgressTreeSlot == nullptr"))
		return;
	}

	ProgressTreeSlot->SetAnchors(FAnchors(0.5, 0.5));
	ProgressTreeSlot->SetPosition(FVector2D(-900, -500));
}

void UGameProgressMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	BTN_Back->OnClicked.AddDynamic(this, &UGameProgressMenu::OnBackClicked);
}

void UGameProgressMenu::DrawTreeLevel(TArray<struct FGameProgressDataStruct*> GameProgressData, int Level)
{
	int RootSide = GameProgressTree->GetRootIconSize().Y;
	int Segments = GameProgressData.Num() * 2 - 1;
	float StartingY = GameProgressTree->GetRootIconPosition().Y - RootSide * (Segments / 2);


	FVector2D RootPosition = GameProgressTree->GetRootIconPosition();

	for (int i = 0; i < Segments; i += 2)
	{
		UGameProgressEntryIcon* Icon = CreateWidget<UGameProgressEntryIcon>(UGameplayStatics::GetGameInstance(GetWorld()), GameProgressTree->GetIconClass());
		Icon->SetEntryName(GameProgressData[i/2]->EntryName);
		FVector2D IconPosition = FVector2D(RootPosition.X + RootSide * (Level * 2 - 2), StartingY + (i * RootSide));
		
		GameProgressTree->AddIconToCanvas(Icon, IconPosition);
	}
}

void UGameProgressMenu::DrawTreeLines(TArray<struct FGameProgressDataStruct*> GameProgressData)
{
	TArray<UWidget*> EntryIcons = GameProgressTree->GetEntryIcons();

	for (int i = 1; i < EntryIcons.Num(); i++) {
		if (GameProgressData[i]->bIsPassed == true) {
			GameProgressTree->ConnectIcons(EntryIcons[GameProgressData[i]->Parent], EntryIcons[i]);
		}
	}
}

void UGameProgressMenu::OnBackClicked()
{
	BackClicked.Broadcast();
}

TArray<UWidget*> UGameProgressMenu::GetEntryIcons()
{
	return GameProgressTree->GetEntryIcons();
}

UGameProgressTreeWidget* UGameProgressMenu::GetProgressTree()
{
	return GameProgressTree;
}

