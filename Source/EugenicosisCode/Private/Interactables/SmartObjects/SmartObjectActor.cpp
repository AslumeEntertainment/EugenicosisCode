// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/SmartObjects/SmartObjectActor.h"
#include "SmartObjectSubsystem.h"
#include "SmartObjectComponent.h"
#include "SmartObjectDefinition.h"
#include "GameplayBehaviorSmartObjectBehaviorDefinition.h"
#include "GameplayBehavior.h"
#include "GameplayBehaviorConfig.h"
#include "EugenicosisCode.h"


// Sets default values
ASmartObjectActor::ASmartObjectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	PrimaryActorTick.bCanEverTick = true;//potentialy false
	SmartObject = CreateDefaultSubobject<USmartObjectComponent>(FName(TEXT("SmartObjectComponent")));
	SetRootComponent(CreateDefaultSubobject<USceneComponent>(FName(TEXT("Root"))));
	SmartObject->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ASmartObjectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

FSmartObjectSlotHandle ASmartObjectActor::GetProperSlotForAgent(AActor* Agent)
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogSmartObjects, Error, TEXT("ASmartObjectActor::GetProperSlotForAgent   IsValid(World) == false"));
		return FSmartObjectSlotHandle();
	}
	USmartObjectSubsystem* SOS = USmartObjectSubsystem::GetCurrent(World);
	if (IsValid(SOS) == false)
	{
		UE_LOG(LogSmartObjects, Error, TEXT("ASmartObjectActor::GetProperSlotForAgent   IsValid(SOS) == false"));
		return FSmartObjectSlotHandle();
	}
	TArray< FSmartObjectSlotHandle > Slots;
	SOS->FindSlots(SmartObject->GetRegisteredHandle(), FSmartObjectRequestFilter(), Slots);
	return Slots[0];
}

// Called every frame
void ASmartObjectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASmartObjectActor::UseSmartObject(AActor* Agent)
{
	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogSmartObjects, Error, TEXT("ASmartObjectActor::UseSmartObjectSlot   IsValid(World) == false"));
		return;
	}
	USmartObjectSubsystem* SOS = USmartObjectSubsystem::GetCurrent(World);
	if (IsValid(SOS) == false)
	{
		UE_LOG(LogSmartObjects, Error, TEXT("ASmartObjectActor::UseSmartObjectSlot   IsValid(SOS) == false"));
		return;
	}
	FSmartObjectSlotHandle Slot = GetProperSlotForAgent(Agent);
	if (Slot.IsValid() == false)
	{
		UE_LOG(LogSmartObjects, Warning, TEXT("ASmartObjectActor::UseSmartObjectSlot   Slot.IsValid() == false"));
		return;
	}
	FSmartObjectClaimHandle Claim = SOS->MarkSlotAsClaimed(Slot);
	if (Claim.IsValid() == false)
	{
		UE_LOG(LogSmartObjects, Warning, TEXT("ASmartObjectActor::UseSmartObjectSlot   Claim.IsValid() == false"));
		return;
	}
	//UE_LOG(LogTemp, Error, TEXT("State: %s"), *(UEnum::GetValueAsString(SOS->GetSlotState(Slot))));
	//UE_LOG(LogTemp, Error, TEXT("%s"), *((SOS->MarkSlotAsOccupied(Claim, UGameplayBehaviorSmartObjectBehaviorDefinition::StaticClass()))->GetClass()->GetName()));
	//UE_LOG(LogTemp, Error, TEXT("State: %s"), *(UEnum::GetValueAsString(SOS->GetSlotState(Slot))));


	const UGameplayBehaviorSmartObjectBehaviorDefinition* GameplayBehaviorSmartObjectBehaviorDefinition = Cast<UGameplayBehaviorSmartObjectBehaviorDefinition>(SOS->MarkSlotAsOccupied(Claim, UGameplayBehaviorSmartObjectBehaviorDefinition::StaticClass()));
	if (!(GameplayBehaviorSmartObjectBehaviorDefinition))
	{
		UE_LOG(LogTemp, Warning, TEXT("3"));
		return;
	}
	UGameplayBehavior* Behavior = GameplayBehaviorSmartObjectBehaviorDefinition->GameplayBehaviorConfig.Get()->GetBehavior(*GetWorld());
	if (!(Behavior))
	{
		UE_LOG(LogTemp, Warning, TEXT("4"));
		return;
	}
	bool bBehaviorTriggerSuccessful = Behavior->Trigger(*Agent, GameplayBehaviorSmartObjectBehaviorDefinition->GameplayBehaviorConfig.Get(), this);
}

void ASmartObjectActor::ReleaseSmartObjectSlot()
{
}


