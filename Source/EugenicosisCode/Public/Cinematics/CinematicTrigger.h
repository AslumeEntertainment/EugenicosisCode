// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CinematicTrigger.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FTriggerCinematicSignature, AActor*, Initiator, int, ID);

class ACinematicManager;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCinematicTrigger : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class EUGENICOSISCODE_API ICinematicTrigger
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CinematicTrigger")
	void AttachToCinematicManager(ACinematicManager* Manager);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CinematicTrigger")
	void TriggerCinematic(int ID = 0);
};
