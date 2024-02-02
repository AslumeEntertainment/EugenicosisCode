// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/SmartObjects/SmartObjectActorWithSkeletalMesh.h"

ASmartObjectActorWithSkeletalMesh::ASmartObjectActorWithSkeletalMesh()
{
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName(TEXT("SkeletalMesh")));
	SkeletalMesh->SetupAttachment(GetRootComponent());
}