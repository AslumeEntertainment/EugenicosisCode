// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/SmartObjects/SmartObjectActorWithSkeletalMesh.h"
#include "SimpleDoor.generated.h"

/**
 *
 */
UCLASS()
class EUGENICOSISCODE_API ASimpleDoor : public ASmartObjectActorWithSkeletalMesh
{
	GENERATED_BODY()


protected:
	UPROPERTY(EditAnywhere)
	bool bIsOpen = false;

public:
	bool GetIsOpen() { return bIsOpen; }

	void UseSmartObject(AActor* Agent) override;

};