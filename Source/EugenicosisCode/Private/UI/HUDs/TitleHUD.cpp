// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUDs/TitleHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#include "Gamemodes/EGC_TitleGameMode.h"
#include "Headers/SaveSystem/GameProgressDataStruct.h"
#include "UI/Widgets/Game/Menus/TitleMenu.h"
#include "UI/Widgets/Game/Menus/GameProgressMenu.h"
#include "UI/Widgets/Game/GameProgressWidgets/GameProgressInfoWidget.h"
#include "UI/Widgets/Game/GameProgressWidgets/GameProgressTreeWidget.h"
#include "UI/Widgets/Game/GameProgressWidgets/GameProgressEntryIcon.h"
#include "UI/Widgets/Game/Menus/SettingsMenu.h"

void ATitleHUD::BeginPlay()
{
	Super::BeginPlay();

	AEGC_TitleGameMode* GameMode = Cast<AEGC_TitleGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!IsValid(GameMode)) 
	{
		UE_LOG(LogTemp, Error, TEXT("ATitleHUD::BeginPlay IsValid(GameMode) == false"));
		return;
	}

	if (PlayerOwner) 
	{
		PlayerOwner->SetInputMode(FInputModeUIOnly());
		PlayerOwner->bShowMouseCursor = true;
	}

	TitleMenu = CreateWidget<UTitleMenu>(UGameplayStatics::GetGameInstance(GetWorld()), TitleMenuClass);
	GameProgressMenu = CreateWidget<UGameProgressMenu>(UGameplayStatics::GetGameInstance(GetWorld()), GameProgressMenuClass);
	GameProgressInfoWidget = CreateWidget<UGameProgressInfoWidget>(UGameplayStatics::GetGameInstance(GetWorld()), GameProgressInfoWidgetClass);
	SettingsMenu = CreateWidget<USettingsMenu>(UGameplayStatics::GetGameInstance(GetWorld()), SettingsMenuClass);

	for (int i = 1; i < GameMode->GetGameProgressDataMaxLevel(); i++)
	{
		TArray<FGameProgressDataStruct*> GameProgressLevelData = GameMode->GetGameProgressionDataByLevel(i+1);
		GameProgressMenu->DrawTreeLevel(GameProgressLevelData, i+1);
	}
	GameProgressMenu->DrawTreeLines(GameMode->GetAllGameProgressionData());

	TitleMenu->ContinueClicked.AddDynamic(this, &ATitleHUD::ShowGameProgressMenu);
	TitleMenu->NewGameClicked.AddDynamic(GameMode, &AEGC_TitleGameMode::StartGame);
	TitleMenu->OptionsClicked.AddDynamic(this, &ATitleHUD::ShowSettingsMenu);
	TitleMenu->QuitClicked.AddDynamic(GameMode, &AEGC_TitleGameMode::QuitGame);

	GameProgressMenu->BackClicked.AddDynamic(this, &ATitleHUD::ShowTitleMenu);
	GameProgressMenu->GetProgressTree()->OnBackgroundPressed.AddDynamic(GameProgressInfoWidget, &UGameProgressInfoWidget::CloseInfo);

	SettingsMenu->BackClicked.AddDynamic(this, &ATitleHUD::ShowTitleMenu);

	GameProgressInfoWidget->BeforeCutsceneClicked.AddDynamic(GameMode, &AEGC_TitleGameMode::StartGame);
	GameProgressInfoWidget->AfterCutsceneClicked.AddDynamic(GameMode, &AEGC_TitleGameMode::StartGame);

	TArray<UWidget*> GameProgressEntries = GameProgressMenu->GetEntryIcons();
	for (UWidget* Entry : GameProgressEntries)
	{
		UGameProgressEntryIcon* Icon = Cast<UGameProgressEntryIcon>(Entry);
		if (Icon)
		{
			Icon->IconClicked.AddDynamic(this, &ATitleHUD::ShowGameProgressInfoWidget);
		}
	}

	ShowTitleMenu();
}

void ATitleHUD::ClearWidgets()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
}

void ATitleHUD::ShowTitleMenu()
{
	ClearWidgets();

	if (!PlayerOwner || !TitleMenu)
	{
		return;
	}

	TitleMenu->AddToViewport();
}

void ATitleHUD::ShowGameProgressMenu()
{
	ClearWidgets();

	if (!PlayerOwner || !GameProgressMenu)
	{
		return;
	}

	GameProgressMenu->AddToViewport();
}

void ATitleHUD::ShowGameProgressInfoWidget(FText IconName)
{
	if (!PlayerOwner || !GameProgressInfoWidget)
	{
		return;
	}

	AEGC_TitleGameMode* GameMode = Cast<AEGC_TitleGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!IsValid(GameMode))
	{
		UE_LOG(LogTemp, Error, TEXT("ATitleHUD::ShowGameProgressInfoWidget IsValid(GameMode) == false"));
		return;
	}

	FGameProgressDataStruct* ProgressEntryData = GameMode->GetGameProgressionEntryByName(IconName);
	if (ProgressEntryData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ATitleHUD::ShowGameProgressInfoWidget ProgressEntryData == nullptr"));
		return;
	}

	if (GameProgressInfoWidget->IsInViewport() && ProgressEntryData->Title.CompareTo(GameProgressInfoWidget->GetTitle()) == 0)
	{
		return;
	}

	if (GameProgressInfoWidget->IsInViewport())
	{
		GameProgressInfoWidget->RemoveFromParent();
	}

	GameProgressInfoWidget->SetTitle(ProgressEntryData->Title);
	GameProgressInfoWidget->SetDescription(ProgressEntryData->Description);
	GameProgressInfoWidget->AddToViewport();
}

void ATitleHUD::ShowSettingsMenu()
{
	ClearWidgets();

	if (!PlayerOwner || !SettingsMenu)
	{
		return;
	}

	SettingsMenu->AddToViewport();
}
