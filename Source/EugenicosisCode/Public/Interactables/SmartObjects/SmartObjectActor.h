// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SmartObjectActor.generated.h"

class USmartObjectComponent;

UCLASS()
class EUGENICOSISCODE_API ASmartObjectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASmartObjectActor();

protected:
	UPROPERTY(EditAnywhere)
	USmartObjectComponent* SmartObject;

protected:
	// Called when the game starts or when spawnd
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
