// Fill out your copyright notice in the Description page of Project Settings.


#include "Cinematics/BasicTriggers/BoxCinematicTrigger.h"

#include "Components/BoxComponent.h"

// Sets default values
ABoxCinematicTrigger::ABoxCinematicTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ABoxCinematicTrigger::OnOverlap);
	SetRootComponent(TriggerBox);
}

void ABoxCinematicTrigger::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	for (FName Tag : TriggeringTags)
	{
		if (OtherActor->ActorHasTag(Tag))
		{
			TriggerCinematic_Implementation();
			return;
		}
	}

}

void ABoxCinematicTrigger::AttachToCinematicManager_Implementation(ACinematicManager* Manager)
{
	OnCinematicRequirementsFulfilled.BindDynamic(Manager, &ACinematicManager::PlaySequence);
}

void ABoxCinematicTrigger::TriggerCinematic_Implementation(int ID)
{
	OnCinematicRequirementsFulfilled.ExecuteIfBound(this, ID);
}

