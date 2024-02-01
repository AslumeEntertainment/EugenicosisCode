// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/SmartObjects/SmartNavLinkBase.h"


    // Sets default values
ASmartNavLinkBase::ASmartNavLinkBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    
}

void ASmartNavLinkBase::BeginPlay()
{
    UE_LOG(LogTemp, Error, TEXT("Actor %s"), *Actor->GetName());
}


