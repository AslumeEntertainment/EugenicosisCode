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
	int Segments = GameProgressData.Num() * 2 - 1;
	float StartingY = 450 - 145 * (Segments / 2);

	FVector2D RootPosition = GameProgressTree->GetRootIconPosition();

	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, RootPosition.ToString());

	for (int i = 0; i < Segments; i += 2)
	{
		UGameProgressEntryIcon* Icon = CreateWidget<UGameProgressEntryIcon>(UGameplayStatics::GetGameInstance(GetWorld()), GameProgressTree->GetIconClass());
		FVector2D IconPosition = FVector2D(RootPosition.X + 145 * (Level * 2 - 2), StartingY + (i * 145));
		
		GameProgressTree->AddIconToCanvas(Icon, IconPosition);

		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, IconPosition.ToString());
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

