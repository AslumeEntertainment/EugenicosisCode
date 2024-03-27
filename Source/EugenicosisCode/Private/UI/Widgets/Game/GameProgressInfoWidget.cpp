// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Game/GameProgressInfoWidget.h"

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

void UGameProgressInfoWidget::SetTitle(FText Title)
{
	TXT_Title->SetText(FText(Title));
}

void UGameProgressInfoWidget::SetDescription(FText Description)
{
	TXT_Description->SetText(FText(Description));
}
