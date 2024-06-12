// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EGC_Character.generated.h"

class UCameraComponent;
class UInputComponent;
class UInputAction;
class UInputMappingContext;
class UCameraShakeBase;
struct FInputActionValue;

DECLARE_DYNAMIC_DELEGATE_OneParam(FEnergyBlurSignature, float, Percentage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractingSignature, FText, ActionText);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPauseNotifySignature);

UCLASS()
class EUGENICOSISCODE_API AEGC_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEGC_Character();

private:
	bool bIsMoving = false;
	bool bIsRunning = false;
	bool bCanInteract = true;

	FTimerHandle GenericTimerHandle;

	UObject* FocusedInteractableObject;
	AActor* FocusedSoundEmitter;

	double CameraHeight;
	double InteractionBoundsSlope;
	double InteractionBoundsOffset;
	double MaxReach;

	void EmitInteractionChecker();
	void CheckForInteractables(FHitResult HitResult);
	void GenericPeriodicFunctionCalls();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	USceneComponent* CharacterAnchorPoint;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* SprintAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* PauseAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Debug)
	bool bShouldPrintDebug = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Debug)
	bool bDebugCameraPitch = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Debug)
	bool bDebugInteracting = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float MaxSprintSpeed = 600;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float MaxWalkSpeed = 300;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float MaxEnergy = 600;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float CurrentEnergy = 600;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float EnergyRechargeRate = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float SprintEnergyDrainRate = -2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CameraMovement, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float EnergyToBlurThreshold = 0.5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Interaction)
	float Reach = 75;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Interaction, meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float LowerReachPercent = 0.85;

	UPROPERTY(EditDefaultsOnly, Category = Interaction)
	UMaterialInterface* InteractionOverlayMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Periodic Generic Functions")
	float GenericCallRate = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CameraMovement)
	TSubclassOf<UCameraShakeBase> IdleCameraShake;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CameraMovement)
	TSubclassOf<UCameraShakeBase> WalkCameraShake;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CameraMovement)
	TSubclassOf<UCameraShakeBase> RunCameraShake;

	UFUNCTION()
	void UpdateEnergy();

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void Interact(const FInputActionValue& Value);

	void ToggleRun(const FInputActionValue& Value);

	void TogglePause(const FInputActionValue& Value);

	void StartCameraMovement(const FInputActionValue& Value);

	void ClearCameraMovement(const FInputActionValue& Value);

	void ToggleCameraShake(TSubclassOf<UCameraShakeBase> CameraShake, bool OnOff = true);

	void ResetCharacterMovement();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void OnFocusedSoundEmitterActive(float InEnvelopeData);

	void SetFocusedSoundEmitter(AActor* FoundSoundEmitter);

	FEnergyBlurSignature OnEnergyRateChanged;
	FEnergyBlurSignature OnFocusedSoundEmitterEnvelopDataUpdated;
	FPauseNotifySignature PauseNotifyDelegate;
	FInteractingSignature OnInteraction;

};
