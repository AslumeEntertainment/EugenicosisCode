// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SO_Door_Base.generated.h"


class USmartObjectComponent;
class UChildActorComponent;


UCLASS()
class EUGENICOSISCODE_API ASO_Door_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASO_Door_Base();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USmartObjectComponent* SmartObjectComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UChildActorComponent* NavLink;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void OnInteraction(AActor* Agent);

};
