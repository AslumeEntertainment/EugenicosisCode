// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/EGC_PlayerController.h"

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
}