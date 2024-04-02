// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamemodes/EGC_TitleGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "Headers/SaveSystem/GameProgressDataStruct.h"

void AEGC_TitleGameMode::BeginPlay()
{
	Super::BeginPlay();

	SwitchCamera(DefaultCameraTag);
}

void AEGC_TitleGameMode::SwitchCamera(FName CameraTag)
{
	APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!IsValid(PlayerController)) 
	{
		return;
	}

	TArray<AActor*> CamerasInLevel;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), CamerasInLevel);

	for (AActor* Actor : CamerasInLevel)
	{
		ACameraActor* CameraActor = Cast<ACameraActor>(Actor);

		if (CameraActor->ActorHasTag(CameraTag)) 
		{
			PlayerController->SetViewTargetWithBlend(CameraActor, 0, EViewTargetBlendFunction::VTBlend_Linear);
		}
	}
}

void AEGC_TitleGameMode::StartGame()
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AEGC_GameModeBase::BeginPlay IsValid(World) == false"));
		return;
	}

	UGameplayStatics::OpenLevel(World, GameplayLevelName);
}

void AEGC_TitleGameMode::QuitGame()
{
	APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!IsValid(PlayerController)) 
	{
		return;
	}

	PlayerController->ConsoleCommand("quit");
}

TArray<struct FGameProgressDataStruct*> AEGC_TitleGameMode::GetAllGameProgressionData()
{
	TArray<FGameProgressDataStruct*> AllRows;
	GameProgressDataDT->GetAllRows(TEXT("AEGC_TitleGameMode::GetAllGameProgressionData"), AllRows);

	return AllRows;
}

TArray<struct FGameProgressDataStruct*> AEGC_TitleGameMode::GetGameProgressionDataByLevel(int Level)
{
	TArray<FGameProgressDataStruct*> WantedRows;

	TArray<FGameProgressDataStruct*> AllRows;
	GameProgressDataDT->GetAllRows(TEXT("AEGC_TitleGameMode::GetAllGameProgressionData"), AllRows);

	for (FGameProgressDataStruct* Row : AllRows) 
	{
		if (Row->Level == Level)
		{
			WantedRows.Add(Row);
		}
	}

	return WantedRows;
}

int AEGC_TitleGameMode::GetGameProgressDataMaxLevel()
{
	TArray<FGameProgressDataStruct*> AllRows;
	GameProgressDataDT->GetAllRows(TEXT("AEGC_TitleGameMode::GetAllGameProgressionData"), AllRows);

	return AllRows[AllRows.Num()-1]->Level;
}
