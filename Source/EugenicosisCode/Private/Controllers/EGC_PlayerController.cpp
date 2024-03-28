// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/EGC_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Gamemodes/EGC_GameModeBase.h"
#include "UI/HUDs/InGameHUD.h"
#include "Characters/EGC_Character.h"

#include "EnhancedInputSubsystems.h"


void AEGC_PlayerController::SwitchInputMappingContext()
{
	AEGC_GameModeBase* GameMode = Cast<AEGC_GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!IsValid(GameMode))
	{
		UE_LOG(LogTemp, Error, TEXT("AEGC_PlayerController::SwitchInputMappingContext IsValid(GameMode) == false"));
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (IsValid(InputSystem) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AEGC_PlayerController::SwitchInputMappingContext IsValid(InputSystem) == false"));
		return;
	}

	if (GameMode->bIsGamePaused()) 
	{
		InputSystem->ClearAllMappings();
		InputSystem->AddMappingContext(UIInputMappingContext, 1);
	}

	else
	{
		InputSystem->ClearAllMappings();
		InputSystem->AddMappingContext(GameplayInputMappingContext, 1);
	}
}

void AEGC_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UEnhancedInputLocalPlayerSubsystem* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (IsValid(InputSystem) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AEGC_PlayerController::OnPossess IsValid(InputSystem) == false"));
		return;
	}

	InputSystem->AddMappingContext(GameplayInputMappingContext, 1);


	AInGameHUD* HUD = Cast<AInGameHUD>(GetHUD());
	if (IsValid(HUD) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEGC_PlayerController::OnPossess IsValid(HUD) == false"));
		return;
	}

	AEGC_Character* PlayerCharacter = Cast<AEGC_Character>(InPawn);
	if (IsValid(Player) == false) {
		UE_LOG(LogTemp, Error, TEXT("AEGC_PlayerController::OnPossess IsValid(Player) == false"));
		return;
	}

	PlayerCharacter->OnEnergyRateChanged.BindDynamic(HUD, &AInGameHUD::SetOverlayBlur);
	PlayerCharacter->PauseNotifyDelegate.AddDynamic(this, &AEGC_PlayerController::SwitchInputMappingContext);
}

