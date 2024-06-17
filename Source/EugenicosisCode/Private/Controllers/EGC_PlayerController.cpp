// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/EGC_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Gamemodes/EGC_GameModeBase.h"
#include "UI/HUDs/InGameHUD.h"
#include "Characters/EGC_Character.h"
#include "Components/SoundEmitterComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"

#include "EnhancedInputSubsystems.h"


AEGC_PlayerController::AEGC_PlayerController()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));

	Hearing = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));
	if (Hearing) 
	{
		Hearing->HearingRange = 40000;
		Hearing->DetectionByAffiliation.bDetectEnemies = true;
		Hearing->DetectionByAffiliation.bDetectFriendlies = true;
		Hearing->DetectionByAffiliation.bDetectNeutrals = true;
		Hearing->SetMaxAge(5);

		PerceptionComponent->SetDominantSense(*Hearing->GetSenseImplementation());
		PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AEGC_PlayerController::OnHearingUpdated);
		PerceptionComponent->ConfigureSense(*Hearing);
	}
}

void AEGC_PlayerController::OnHearingUpdated(TArray<AActor*> const& UpdatedActors)
{
	AActor* LatestInstigator = UpdatedActors.Last();
	USoundEmitterComponent* SoundEmitterComponent = Cast<USoundEmitterComponent>(LatestInstigator->GetComponentByClass(USoundEmitterComponent::StaticClass()));
	if (!IsValid(SoundEmitterComponent))
	{
		return;
	}

	AEGC_Character* PlayerPawn = Cast<AEGC_Character>(GetPawn());
	if (!IsValid(PlayerPawn))
	{
		UE_LOG(LogTemp, Error, TEXT("AEGC_PlayerController::OnHearingUpdated IsValid(PlayerPawn) == false"));
		return;
	}

	PlayerPawn->SetFocusedSoundEmitter(LatestInstigator);
	SoundEmitterComponent->OnAmplitudeEnvelopeDataUpdated.BindDynamic(PlayerPawn, &AEGC_Character::OnFocusedSoundEmitterActive);

	if (LatestInstigator->ActorHasTag(FName("Big")))
	{
		GEngine->AddOnScreenDebugMessage(100, 5, FColor::Orange, TEXT("Notification sound is being detected!"));
	}

	if (LatestInstigator->ActorHasTag(FName("Chungus")))
	{
		GEngine->AddOnScreenDebugMessage(100, 5, FColor::Orange, TEXT("VineBoom sound is being detected!"));
	}
}

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

