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
	
public:

	AEGC_PlayerController();

private:

	class UAISenseConfig_Hearing* Hearing;

	UFUNCTION()
	void OnHearingUpdated(TArray<AActor*> const& UpdatedActors);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* GameplayInputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* UIInputMappingContext;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Perception, meta = (AllowPrivateAccess = "true"))
	class UAIPerceptionComponent* PerceptionComponent;

	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
	void SwitchInputMappingContext();

};
