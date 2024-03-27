// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamemodes/EGC_GameModeBase.h"

#include "Controllers/EGC_PlayerController.h"
#include "Characters/EGC_Character.h"
#include "UI/HUDs/InGameHUD.h"

#include "Kismet/GameplayStatics.h"

void AEGC_GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	AInGameHUD* HUD = Cast<AInGameHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	if (IsValid(HUD) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AEGC_GameModeBase::BeginPlay IsValid(HUD) == false"));
		return;
	}

	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AEGC_GameModeBase::BeginPlay IsValid(World) == false"));
		return;
	}

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AEGC_Character* Character = World->SpawnActor<AEGC_Character>(CharacterClass, CharacterStartLocation, CharacterStartRotation, Params); ;
	if (IsValid(Character) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AEGC_GameModeBase::BeginPlay IsValid(MainPawn) == false"));
		return;
	}


	AEGC_PlayerController* PlayerController = Cast<AEGC_PlayerController>(UGameplayStatics::GetPlayerController(World, 0));
	if (IsValid(PlayerController) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AEGC_GameModeBase::BeginPlay IsValid(PlayerController) == false"));
		return;
	}

	Character->PauseNotifyDelegate.AddDynamic(this, &AEGC_GameModeBase::PauseGame);

	PlayerController->Possess(Character);
}

void AEGC_GameModeBase::PauseGame()
{
	bIsPaused = !bIsPaused;

	AInGameHUD* HUD = Cast<AInGameHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
	if (IsValid(HUD) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AEGC_GameModeBase::BeginPlay IsValid(HUD) == false"));
		return;
	}
	
	HUD->TogglePauseMenu(bIsPaused);
}

bool AEGC_GameModeBase::bIsGamePaused()
{
	return bIsPaused;
}

void AEGC_GameModeBase::ReturnToTitle()
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AEGC_GameModeBase::BeginPlay IsValid(World) == false"));
		return;
	}

	UGameplayStatics::OpenLevel(World, TitleMenuLevelName);
}

void AEGC_GameModeBase::QuitGame()
{
	APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!IsValid(PlayerController))
	{
		return;
	}

	PlayerController->ConsoleCommand("quit");
}
