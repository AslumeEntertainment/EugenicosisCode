// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "SoundEmitterSphereComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSoundEmitterLostSignature);

UCLASS(ClassGroup = (EGC_Components))
class EUGENICOSISCODE_API USoundEmitterSphereComponent : public USphereComponent
{
	GENERATED_BODY()
	
public:
	USoundEmitterSphereComponent();

	FSoundEmitterLostSignature OnSoundEmitterLost;

private:
	FTimerHandle SoundEmitterLostTimer;

	UFUNCTION()
	void SoundEmitterLost();

	UFUNCTION()
	void OnPlayerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnPlayerEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
