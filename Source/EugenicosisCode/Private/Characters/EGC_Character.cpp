// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EGC_Character.h"

#include "Gamemodes/EGC_GameModeBase.h"
#include "Interactables/Interactable.h"
#include "Components/SoundEmitterSphereComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "EugenicosisCode.h"
#include "Camera/CameraComponent.h"
#include "Components/AudioComponent.h"



// Sets default values
AEGC_Character::AEGC_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CharacterAnchorPoint = CreateDefaultSubobject<USceneComponent>(TEXT("AnchorPoint"));
	CharacterAnchorPoint->SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->SetupAttachment(GetRootComponent());
	CameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 60.f));
	CameraComponent->bUsePawnControlRotation = true;
}

void AEGC_Character::BeginPlay()
{
	Super::BeginPlay();
}

void AEGC_Character::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	ToggleCameraShake(IdleCameraShake);
	OnEnergyRateChanged.ExecuteIfBound(1);

	CameraHeight = CameraComponent->GetComponentLocation().Z - CharacterAnchorPoint->GetComponentLocation().Z;
	InteractionBoundsSlope = CameraHeight / (Reach - Reach * LowerReachPercent);
	InteractionBoundsOffset = -InteractionBoundsSlope * Reach * LowerReachPercent;
	FVector2D CameraLocation = FVector2D(0, CameraHeight);
	FVector2D LowerReachBound = FVector2D(Reach * LowerReachPercent, 0);
	MaxReach = FMath::Sqrt(FMath::Pow(CameraLocation.X-LowerReachBound.X, 2) + FMath::Pow(CameraLocation.Y - LowerReachBound.Y, 2));

	GetWorldTimerManager().SetTimer(GenericTimerHandle, this, &AEGC_Character::GenericPeriodicFunctionCalls, GenericCallRate, true, 0.01f);
}

void AEGC_Character::GenericPeriodicFunctionCalls()
{
	UpdateEnergy();
}

// Called every frame
void AEGC_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	EmitInteractionChecker();
}

void AEGC_Character::EmitInteractionChecker()
{
	float ModifiedReach = Reach;
	float CameraPitch = CameraComponent->GetComponentRotation().Pitch;
	float CameraTan = FMath::Tan(FMath::DegreesToRadians(CameraPitch));
	float X = (InteractionBoundsOffset - CameraHeight) / ( - InteractionBoundsSlope);
	float Y = ((InteractionBoundsOffset * CameraTan) - (CameraHeight * InteractionBoundsSlope)) / (CameraTan - InteractionBoundsSlope);
	FVector2D PlanerInteractionEndPoint = FVector2D(X, Y);
	
	ModifiedReach = FMath::Clamp(FMath::Sqrt(FMath::Pow(PlanerInteractionEndPoint.X, 2) + FMath::Pow(PlanerInteractionEndPoint.Y - CameraHeight, 2)), Reach, MaxReach);
	FVector StartTrace = CameraComponent->GetComponentLocation();
	FVector EndTrace = CameraComponent->GetForwardVector() * ModifiedReach + StartTrace;
	
	const FName TraceTag("InteractableTraceTag");

	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogCharacter, Error, TEXT("AEGC_Character::EmitInteractionChecker IsValid(World) == false"));
		return;
	}

	FHitResult HitResult;
	FCollisionQueryParams CQP;
	CQP.AddIgnoredActor(this);
	CQP.TraceTag = TraceTag;

	if (bShouldPrintDebug)
	{
		if (bDebugInteracting)
		{
			World->DebugDrawTraceTag = TraceTag;
		}
		if (bDebugCameraPitch)
		{
			UE_LOG(LogCharacter, Warning, TEXT("Camera Pitch - %f\nTan - %f"), CameraPitch, CameraTan);
			UE_LOG(LogCharacter, Warning, TEXT("Reach - %f / (%f - %f)"), ModifiedReach, Reach, MaxReach);
		}
	}

	World->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_GameTraceChannel1, CQP);

	CheckForInteractables(HitResult);
}

void AEGC_Character::CheckForInteractables(FHitResult HitResult)
{
	if (bCanInteract == false)
	{
		FocusedInteractableObject = nullptr;
		OnInteraction.Broadcast(FText());
	}

	AActor* HitActor = HitResult.GetActor();
	UPrimitiveComponent* HitComponent = HitResult.GetComponent();
	IInteractable* InteractableActor = Cast<IInteractable>(HitActor);
	IInteractable* InteractableComponent = Cast<IInteractable>(HitComponent);

	if (HitActor == nullptr)
	{
		if (FocusedInteractableObject && Cast<AActor>(FocusedInteractableObject)->GetComponentByClass(UMeshComponent::StaticClass()))
		{
			UActorComponent* InteractableMeshComponent = Cast<AActor>(FocusedInteractableObject)->GetComponentByClass(UMeshComponent::StaticClass());
			if (Cast<UMeshComponent>(InteractableMeshComponent))
			{
				Cast<UMeshComponent>(InteractableMeshComponent)->SetOverlayMaterial(nullptr);
			}
		}
		
		FocusedInteractableObject = nullptr;
		OnInteraction.Broadcast(FText());
		return;
	}
	if (InteractableComponent != nullptr)
	{
		FocusedInteractableObject = HitComponent;
		OnInteraction.Broadcast(InteractableComponent->Execute_DisplayInteractText(HitComponent));
		return;
	}
	if (InteractableActor == nullptr)
	{
		if (FocusedInteractableObject && Cast<AActor>(FocusedInteractableObject)->GetComponentByClass(UMeshComponent::StaticClass()))
		{
			UActorComponent* InteractableMeshComponent = Cast<AActor>(FocusedInteractableObject)->GetComponentByClass(UMeshComponent::StaticClass());
			if (Cast<UMeshComponent>(InteractableMeshComponent))
			{
				Cast<UMeshComponent>(InteractableMeshComponent)->SetOverlayMaterial(nullptr);
			}
		}

		FocusedInteractableObject = nullptr;
		OnInteraction.Broadcast(FText());
		return;
	}

	UMeshComponent* HitMeshComponent = Cast<UMeshComponent>(HitComponent);
	if (HitMeshComponent != nullptr)
	{
		HitMeshComponent->SetOverlayMaterial(InteractionOverlayMaterial);
	}

	FocusedInteractableObject = HitActor;
	OnInteraction.Broadcast(InteractableActor->Execute_DisplayInteractText(HitActor));
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

void AEGC_Character::Interact(const FInputActionValue& Value)
{
	if (IsValid(FocusedInteractableObject) == false)
	{
		if (bShouldPrintDebug && bDebugInteracting)
		{
			UE_LOG(LogCharacter, Warning, TEXT("No Interaction Objbect"));
		}
		return;
	}
	Cast<IInteractable>(FocusedInteractableObject)->Execute_InteractRequest(FocusedInteractableObject, this);
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

void AEGC_Character::TogglePause(const FInputActionValue& Value)
{
	PauseNotifyDelegate.Broadcast();

	AEGC_GameModeBase* GameMode = Cast<AEGC_GameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!IsValid(GameMode))
	{
		UE_LOG(LogCharacter, Error, TEXT("AEGC_Character::TogglePause IsValid(GameMode) == false"));
		return;
	}

	if (GameMode->bIsGamePaused())
	{
		ResetCharacterMovement();
		GetWorldTimerManager().PauseTimer(GenericTimerHandle);

		/*
		if (!IsValid(FocusedSoundEmitter))
		{
			return;
		}

		USoundEmitterSphereComponent* SoundEmitterComp = Cast<USoundEmitterSphereComponent>(FocusedSoundEmitter->GetComponentByClass(USoundEmitterSphereComponent::StaticClass()));
		GetWorldTimerManager().PauseTimer(SoundEmitterComp->SoundEmitterLostTimer);
		*/
	}
	else
	{
		GetWorldTimerManager().UnPauseTimer(GenericTimerHandle);

		/*
		if (!IsValid(FocusedSoundEmitter))
		{
			return;
		}

		USoundEmitterSphereComponent* SoundEmitterComp = Cast<USoundEmitterSphereComponent>(FocusedSoundEmitter->GetComponentByClass(USoundEmitterSphereComponent::StaticClass()));
		GetWorldTimerManager().UnPauseTimer(SoundEmitterComp->SoundEmitterLostTimer);
		*/
	}
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
		UE_LOG(LogCharacter, Error, TEXT("AEGC_Character::ActivateCameraShake IsValid(Controller) == false"));
		return;
	}
	OnOff ? PC->ClientStartCameraShake(CameraShake) : PC->ClientStopCameraShake(CameraShake);
}

void AEGC_Character::ResetCharacterMovement()
{
	bIsMoving = false;
	bIsRunning = false;

	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->MaxWalkSpeed = MaxWalkSpeed;
	
	ToggleCameraShake(IdleCameraShake);
	ToggleCameraShake(WalkCameraShake, false);
	ToggleCameraShake(RunCameraShake, false);
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
	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AEGC_Character::Interact);
	EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AEGC_Character::ToggleRun);
	EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &AEGC_Character::TogglePause);
}

void AEGC_Character::OnFocusedSoundEmitterActive(float InEnvelopeData)
{
	if (!IsValid(FocusedSoundEmitter))
	{
		UE_LOG(LogCharacter, Error, TEXT("AEGC_Character::OnFocusedSoundEmitterActive IsValid(FocusedSoundEmitter) == false"));
		return;
	}

	FVector PlayerLocation = GetActorLocation();
	FVector SoundEmitterLocation = FocusedSoundEmitter->GetActorLocation();

	FVector Direction = UKismetMathLibrary::GetDirectionUnitVector((PlayerLocation), SoundEmitterLocation);
	float Distance = UKismetMathLibrary::Vector_Distance(PlayerLocation, SoundEmitterLocation);
	float HorizontalDirectionValue = UKismetMathLibrary::Dot_VectorVector(CameraComponent->GetRightVector(), Direction);
	float VerticalDirectionValue = UKismetMathLibrary::Dot_VectorVector(CameraComponent->GetUpVector(), Direction) * -1; //We multiply this value by -1 because of UE's coordinate system

	GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, FString::Printf(TEXT("Sound Emitter found %.2f meters away!"), Distance / 100));
	GEngine->AddOnScreenDebugMessage(11, 1, FColor::Green, FString::Printf(TEXT("Horizontal direction value: %f"), HorizontalDirectionValue));
	GEngine->AddOnScreenDebugMessage(12, 1, FColor::Green, FString::Printf(TEXT("Vertical direction value: %f"), VerticalDirectionValue));

	UAudioComponent* SoundEmitterAudioComp = Cast<UAudioComponent>(FocusedSoundEmitter->GetComponentByClass(UAudioComponent::StaticClass()));
	if (!IsValid(SoundEmitterAudioComp))
	{
		UE_LOG(LogCharacter, Error, TEXT("AEGC_Character::OnFocusedSoundEmitterActive IsValid(SoundEmitterAudioComp) == false"));
		return;
	}

	float DistanceVolumeMultiplier = 1 - Distance / SoundEmitterAudioComp->Sound->MaxDistance;

	OnFocusedSoundEmitterEnvelopDataUpdated.ExecuteIfBound(DistanceVolumeMultiplier * InEnvelopeData); 
}

void AEGC_Character::SetFocusedSoundEmitter(AActor* FoundSoundEmitter)
{
	FocusedSoundEmitter = FoundSoundEmitter;
}





