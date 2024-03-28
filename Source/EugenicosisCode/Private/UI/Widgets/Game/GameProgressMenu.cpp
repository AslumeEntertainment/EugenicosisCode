// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Game/GameProgressMenu.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/WrapBox.h"
#include "UI/Widgets/Game/GameProgressEntryIcon.h"

void UGameProgressMenu::OnBackClicked()
{
	BackClicked.Broadcast();
}

void UGameProgressMenu::OnBackgroundClicked()
{
	BackgroundClicked.Broadcast();
}

void UGameProgressMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	BTN_Back->OnClicked.AddDynamic(this, &UGameProgressMenu::OnBackClicked);
	BTN_Background->OnClicked.AddDynamic(this, &UGameProgressMenu::OnBackgroundClicked);
}

void UGameProgressMenu::AddEntryIcon(UGameProgressEntryIcon* EntryIcon)
{
	EntryBox->AddChild(EntryIcon);
	ReloadLines();
}

TArray<UWidget*> UGameProgressMenu::GetEntryIcons()
{
	return EntryBox->GetAllChildren();
}

void UGameProgressMenu::ReloadLines()
{
	/*
	for (int i = 1; i < EntryBox->GetChildrenCount(); i++)
	{
		UWidgetBlueprintLibrary::DrawLine(EntryBox->GetChildAt(i), EntryBox->GetChildAt(i-1), FLinearColor::White, true, 5);
	}
	*/
}
