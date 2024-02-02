// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/SmartObjects/SmartObjectActor.h"
#include "SmartObjectActorWithSkeletalMesh.generated.h"

/**
 * 
 */
UCLASS()
class EUGENICOSISCODE_API ASmartObjectActorWithSkeletalMesh : public ASmartObjectActor
{
	GENERATED_BODY()
	
public:
	ASmartObjectActorWithSkeletalMesh();

protected:
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* SkeletalMesh;

public:
	USkeletalMeshComponent* GetMesh(){return SkeletalMesh;}
	
};
