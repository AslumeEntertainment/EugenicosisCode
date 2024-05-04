// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Game/GameProgressWidgets/GameProgressInfoWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

void UGameProgressInfoWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	BTN_StartBeforeCutscene->OnClicked.AddDynamic(this, &UGameProgressInfoWidget::OnBeforeCutsceneClicked);
	BTN_StartAfterCutscene->OnClicked.AddDynamic(this, &UGameProgressInfoWidget::OnAfterCutsceneClicked);
}

void UGameProgressInfoWidget::OnBeforeCutsceneClicked()
{
	BeforeCutsceneClicked.Broadcast();
}

void UGameProgressInfoWidget::OnAfterCutsceneClicked()
{
	AfterCutsceneClicked.Broadcast();
}

void UGameProgressInfoWidget::CloseInfo_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("UGameProgressInfoWidget::CloseInfo No blueprint implementation exists for function"));
	RemoveFromParent();
}

void UGameProgressInfoWidget::SetTitle(FText Title)
{
	TXT_Title->SetText(FText(Title));
}

void UGameProgressInfoWidget::SetDescription(FText Description)
{
	TXT_Description->SetText(FText(Description));
}

FText UGameProgressInfoWidget::GetTitle()
{
	return TXT_Title->GetText();
}
