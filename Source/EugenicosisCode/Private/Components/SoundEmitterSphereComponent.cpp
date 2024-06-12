// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SoundEmitterSphereComponent.h"
#include "Characters/EGC_Character.h"

USoundEmitterSphereComponent::USoundEmitterSphereComponent()
{
	OnComponentBeginOverlap.AddDynamic(this, &USoundEmitterSphereComponent::OnPlayerBeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &USoundEmitterSphereComponent::OnPlayerEndOverlap);
}

void USoundEmitterSphereComponent::SoundEmitterLost()
{
	GEngine->AddOnScreenDebugMessage(5, 20, FColor::Red, TEXT("Sound Emitter Lost!!!"));
	OnSoundEmitterLost.Broadcast();
}

void USoundEmitterSphereComponent::OnPlayerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEGC_Character* Player = Cast<AEGC_Character>(OtherActor);
	if (!IsValid(Player)) 
	{
		UE_LOG(LogTemp, Error, TEXT("USoundEmitterSphereComponent::OnPlayerBeginOverlap IsValid(Player) == false"));
		return;
	}

	/*
	if (!IsValid(GetWorld()))
	{
		UE_LOG(LogTemp, Error, TEXT("USoundEmitterSphereComponent::OnPlayerBeginOverlap IsValid(GetWorld()) == false"));
		return;
	}

	GetWorld()->GetTimerManager().ClearTimer(SoundEmitterLostTimer);
	*/
	Player->SetFocusedSoundEmitter(GetOwner());
}

void USoundEmitterSphereComponent::OnPlayerEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AEGC_Character* Player = Cast<AEGC_Character>(OtherActor);
	if (!IsValid(Player))
	{
		UE_LOG(LogTemp, Error, TEXT("USoundEmitterSphereComponent::OnPlayerEndOverlap IsValid(Player) == false"));
		return;
	}

	/*
	if (!IsValid(GetWorld()))
	{
		UE_LOG(LogTemp, Error, TEXT("USoundEmitterSphereComponent::OnPlayerEndOverlap IsValid(GetWorld()) == false"));
		return;
	}
	
	GetWorld()->GetTimerManager().SetTimer(SoundEmitterLostTimer, this, &USoundEmitterSphereComponent::SoundEmitterLost, 10, false);
	*/
	Player->SetFocusedSoundEmitter(nullptr);
}
