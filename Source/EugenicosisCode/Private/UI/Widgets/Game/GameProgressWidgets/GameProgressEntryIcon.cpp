// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Game/GameProgressWidgets/GameProgressEntryIcon.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

void UGameProgressEntryIcon::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	BTN_Icon->OnClicked.AddDynamic(this, &UGameProgressEntryIcon::OnIconClicked);
}

void UGameProgressEntryIcon::OnIconClicked()
{
	IconClicked.Broadcast(TXT_EntryName->GetText());
}

void UGameProgressEntryIcon::SetEntryName(FText EntryName)
{
	TXT_EntryName->SetText(FText(EntryName));
}
