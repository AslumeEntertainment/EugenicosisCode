// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Navigation/NavLinkProxy.h"
#include "SmartNavLinkBase.generated.h"


class UNavLinkDefinition;
class UNavLinkCustomComponent;

UCLASS()
class EUGENICOSISCODE_API ASmartNavLinkBase : public ANavLinkProxy
{
    GENERATED_BODY()

public:

    ASmartNavLinkBase(const FObjectInitializer& ObjectInitializer);

protected:
    UPROPERTY(EditAnywhere)
    AActor* Actor;

public:
    void BeginPlay() override;
};