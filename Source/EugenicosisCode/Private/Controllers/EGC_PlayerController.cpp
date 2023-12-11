// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/EGC_PlayerController.h"
#include "UI/HUDs/InGameHUD.h"
#include "Characters/EGC_Character.h"

#include "EnhancedInputSubsystems.h"

void AEGC_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UEnhancedInputLocalPlayerSubsystem* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (IsValid(InputSystem) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("AEGC_PlayerController::OnPossess IsValid(InputSystem) == false"));
		return;
	}

	InputSystem->AddMappingContext(InputMappingContext, 0);


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
}