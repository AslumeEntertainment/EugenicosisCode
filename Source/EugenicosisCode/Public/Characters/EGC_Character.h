// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EGC_Character.generated.h"

class UInputComponent;
class UInputAction;
class UInputMappingContext;
class UCameraShakeBase;
struct FInputActionValue;

UDELEGATE()
DECLARE_DYNAMIC_DELEGATE_OneParam(FEnergyBlurSignature, float, Percentage);
UDELEGATE()
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
	bool bIsPaused = false;

	FTimerHandle EnergyTimerHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* SprintAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* PauseAction;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CameraMovement)
	TSubclassOf<class UCameraShakeBase> IdleCameraShake;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CameraMovement)
	TSubclassOf<class UCameraShakeBase> WalkCameraShake;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CameraMovement)
	TSubclassOf<class UCameraShakeBase> RunCameraShake;

	UFUNCTION()
	void UpdateEnergy();

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void ToggleRun(const FInputActionValue& Value);

	void TogglePause(const FInputActionValue& Value);

	void StartCameraMovement(const FInputActionValue& Value);

	void ClearCameraMovement(const FInputActionValue& Value);

	void ToggleCameraShake(TSubclassOf<class UCameraShakeBase> CameraShake, bool OnOff = true);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FEnergyBlurSignature OnEnergyRateChanged;
	FPauseNotifySignature PauseNotifyDelegate;

};
