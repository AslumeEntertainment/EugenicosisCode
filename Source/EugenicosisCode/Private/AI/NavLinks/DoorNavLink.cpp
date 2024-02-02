// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NavLinks/DoorNavLink.h"
#include "Interactables/SmartObjects/SimpleDoor.h"
#include "EugenicosisCode.h"


void ADoorNavLink::ReceiveLinkReached(AActor* MovingActor, const FVector& DestinationPoint)
{
	ASimpleDoor* Door = Cast<ASimpleDoor>(SmartObject);
	if (IsValid(Door) == false)
	{
		UE_LOG(LogSmartObjects, Error, TEXT("ADoorNavLink::ReceiveLinkReached    SmartObject is not of type ASimpleDoor"));
		return;
	}
	if (Door->GetIsOpen() == false)
	{
		Super::ReceiveLinkReached(MovingActor, DestinationPoint);
	}
}