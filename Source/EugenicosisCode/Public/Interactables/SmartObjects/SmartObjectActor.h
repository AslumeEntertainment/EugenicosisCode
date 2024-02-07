// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SmartObjectRuntime.h"
#include "SmartObjectActor.generated.h"

class USmartObjectComponent;
class UGameplayBehavior;
struct FSmartObjectSlotHandle;
//struct FSmartObjectClaimHandle;


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

	UPROPERTY(EditAnywhere)
	TMap<AActor*, FSmartObjectClaimHandle> Users;



protected:
	// Called when the game starts or when spawnd
	virtual void BeginPlay() override;

	virtual FSmartObjectSlotHandle GetProperSlotForAgent(AActor* Agent);

	//void OccupySlot(FSmartObjectSlotHandle* ClaimHandle);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	virtual void UseSmartObject(AActor* Agent);

	void ReleaseSmartObjectSlot(UGameplayBehavior& Behavior, AActor& Avatar, const bool bInterrupted);
};
