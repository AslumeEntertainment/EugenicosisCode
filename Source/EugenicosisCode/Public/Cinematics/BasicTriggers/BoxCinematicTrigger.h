// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Cinematics/CinematicTrigger.h"

#include "BoxCinematicTrigger.generated.h"

class UBoxComponent;

UCLASS()
class EUGENICOSISCODE_API ABoxCinematicTrigger : public AActor, public ICinematicTrigger
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoxCinematicTrigger();


protected:

	FTriggerCinematicSignature OnCinematicRequirementsFulfilled;

	UPROPERTY()
	UBoxComponent* TriggerBox;

	UPROPERTY(EditAnywhere)
	TArray<FName> TriggeringTags;


protected:

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
				   int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:	

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CinematicTrigger")
	void AttachToCinematicManager(ACinematicManager* Manager);
	void AttachToCinematicManager_Implementation(ACinematicManager* Manager);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "CinematicTrigger")
	void TriggerCinematic(int ID = 0);
	virtual void TriggerCinematic_Implementation(int ID = 0);
};
