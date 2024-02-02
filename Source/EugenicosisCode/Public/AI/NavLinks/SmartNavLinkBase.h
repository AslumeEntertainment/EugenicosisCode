// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Navigation/NavLinkProxy.h"
#include "SmartNavLinkBase.generated.h"


class UNavLinkDefinition;
class UNavLinkCustomComponent;
class ASmartObjectActor;

UCLASS()
class EUGENICOSISCODE_API ASmartNavLinkBase : public ANavLinkProxy
{
    GENERATED_BODY()



public:

    ASmartNavLinkBase();


protected:
    UPROPERTY(EditAnywhere)
    ASmartObjectActor* SmartObject;

protected:
    UFUNCTION()
    virtual void ReceiveLinkReached(AActor* MovingActor, const FVector& DestinationPoint);

public:
    void BeginPlay() override;
};