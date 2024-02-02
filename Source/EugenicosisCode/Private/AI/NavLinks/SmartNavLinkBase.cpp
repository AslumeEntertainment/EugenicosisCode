// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NavLinks/SmartNavLinkBase.h"
#include "Interactables/SmartObjects/SmartObjectActor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "EugenicosisCode.h"

    // Sets default values
ASmartNavLinkBase::ASmartNavLinkBase()
{
    OnSmartLinkReached.AddDynamic(this, &ASmartNavLinkBase::ReceiveLinkReached);
    

}

void ASmartNavLinkBase::ReceiveLinkReached(AActor* MovingActor, const FVector& DestinationPoint)
{
    SmartObject->UseSmartObject(MovingActor);
}

void ASmartNavLinkBase::BeginPlay()
{
    if (IsValid(SmartObject) == false)
    {
        UE_LOG(LogSmartObjects, Error, TEXT("ASmartNavLinkBase::ASmartNavLinkBase()   IsValid(SmartObject) == false  from %s"), *GetName());
        UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, true);
    }
}


