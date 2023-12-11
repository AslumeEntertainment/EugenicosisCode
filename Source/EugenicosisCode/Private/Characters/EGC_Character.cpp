// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EGC_Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(Log_EGC_Character);

// Sets default values
AEGC_Character::AEGC_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEGC_Character::BeginPlay()
{
	Super::BeginPlay();
}

void AEGC_Character::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	ToggleCameraShake(IdleCameraShake);
	OnEnergyRateChanged.ExecuteIfBound(1);
	GetWorldTimerManager().SetTimer(EnergyTimerHandle, this, &AEGC_Character::UpdateEnergy, 0.5f, true, 0.01f);
}



// Called every frame
void AEGC_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEGC_Character::UpdateEnergy()
{
	CurrentEnergy += bIsRunning ? SprintEnergyDrainRate : EnergyRechargeRate;

	CurrentEnergy = FMath::Clamp(CurrentEnergy, 0, MaxEnergy);

	if ( (CurrentEnergy / MaxEnergy) > EnergyToBlurThreshold)
	{
		OnEnergyRateChanged.ExecuteIfBound(1);
		return;
	}

	OnEnergyRateChanged.ExecuteIfBound(CurrentEnergy / (MaxEnergy * EnergyToBlurThreshold));

}

void AEGC_Character::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(), MovementVector.Y);
	AddMovementInput(GetActorRightVector(), MovementVector.X);
}

void AEGC_Character::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void AEGC_Character::ToggleRun(const FInputActionValue& Value)
{
	bIsRunning = Value.Get<bool>();

	UCharacterMovementComponent* Movement = GetCharacterMovement();

	Movement->MaxWalkSpeed = bIsRunning ? MaxSprintSpeed : MaxWalkSpeed;

	if (bIsMoving == false)
	{
		return;
	}

	ToggleCameraShake(bIsRunning ? RunCameraShake : WalkCameraShake);
	ToggleCameraShake(bIsRunning ? WalkCameraShake : RunCameraShake, false);
	
}

void AEGC_Character::StartCameraMovement(const FInputActionValue& Value)
{
	bIsMoving = true;
	ToggleCameraShake(IdleCameraShake, false);
	ToggleCameraShake(GetCharacterMovement()->MaxWalkSpeed > 300 ? RunCameraShake : WalkCameraShake);
	ToggleCameraShake(GetCharacterMovement()->MaxWalkSpeed > 300 ? WalkCameraShake : RunCameraShake, false);
}

void AEGC_Character::ClearCameraMovement(const FInputActionValue& Value)
{
	bIsMoving = false;
	ToggleCameraShake(IdleCameraShake);
	ToggleCameraShake(WalkCameraShake, false);
	ToggleCameraShake(RunCameraShake, false);
}

void AEGC_Character::ToggleCameraShake(TSubclassOf<class UCameraShakeBase> CameraShake, bool OnOff)
{
	APlayerController* PC = Cast<APlayerController>(Controller);
	if (IsValid(PC) == false)
	{
		UE_LOG(Log_EGC_Character, Error, TEXT("AEGC_Character::ActivateCameraShake IsValid(Controller) == false"));
		return;
	}
	OnOff ? PC->ClientStartCameraShake(CameraShake) : PC->ClientStopCameraShake(CameraShake);
}

// Called to bind functionality to input
void AEGC_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AEGC_Character::Move);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &AEGC_Character::StartCameraMovement);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AEGC_Character::ClearCameraMovement);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AEGC_Character::Look);
	EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AEGC_Character::ToggleRun);


}



