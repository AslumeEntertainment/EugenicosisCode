// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/Interactable.h"
#include "SimpleDoor.generated.h"

/**
 *
 */
UCLASS()
class EUGENICOSISCODE_API ASimpleDoor : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	ASimpleDoor();

protected:
	UPROPERTY(EditAnywhere)
	bool bIsOpen = false;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* SkeletalMesh;

public:
	bool GetIsOpen() { return bIsOpen; }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CinematicTrigger")
	void InteractRequest(AEGC_Character* InteractingCharacter);
	virtual void InteractRequest_Implementation(AEGC_Character* InteractingCharacter);

};