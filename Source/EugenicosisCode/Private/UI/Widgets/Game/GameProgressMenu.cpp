// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Game/GameProgressMenu.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "Components/CanvasPanelSlot.h"

#include "UI/Widgets/Game/GameProgressEntryIcon.h"
#include "UI/Widgets/Game/GameProgressTreeWidget.h"
#include "Headers/SaveSystem/GameProgressDataStruct.h"


void UGameProgressMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	BTN_Back->OnClicked.AddDynamic(this, &UGameProgressMenu::OnBackClicked);
	BTN_Background->OnClicked.AddDynamic(this, &UGameProgressMenu::OnBackgroundClicked);
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

void UGameProgressMenu::OnBackgroundClicked()
{
	BackgroundClicked.Broadcast();
}

TArray<UWidget*> UGameProgressMenu::GetEntryIcons()
{
	return GameProgressTree->GetEntryIcons();
}

