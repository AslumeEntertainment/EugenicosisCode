// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EGC_PlayerController.generated.h"

class UInputMappingContext;


UCLASS()
class EUGENICOSISCODE_API AEGC_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* GameplayInputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* UIInputMappingContext;

	UFUNCTION()
	void SwitchInputMappingContext();

protected:

	virtual void OnPossess(APawn* InPawn) override;

};
