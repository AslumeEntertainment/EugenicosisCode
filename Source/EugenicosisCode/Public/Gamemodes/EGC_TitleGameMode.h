// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EGC_TitleGameMode.generated.h"


UCLASS()
class EUGENICOSISCODE_API AEGC_TitleGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	FName GameplayLevelName = FName("Residence");

	UPROPERTY(EditAnywhere)
	FName DefaultCameraTag = FName("CamAct1");

	UPROPERTY(EditDefaultsOnly)
	class UDataTable* GameProgressDataDT;

	void SwitchCamera(FName CameraTag);

public:

	UFUNCTION()
	void StartGame();

	UFUNCTION()
	void QuitGame();

	TArray<struct FGameProgressDataStruct*> GetAllGameProgressionData();

	TArray<struct FGameProgressDataStruct*> GetGameProgressionDataByLevel(int Level);

	struct FGameProgressDataStruct* GetGameProgressionEntryByName(FText EntryName);

	int GetGameProgressDataMaxLevel();

};
