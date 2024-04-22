#include "Interactables/BasicInteractables/SimpleDoor.h"

#include "Characters/EGC_Character.h"


ASimpleDoor::ASimpleDoor()
{
	SetRootComponent(CreateDefaultSubobject<USceneComponent>(FName(TEXT("Root"))));
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName(TEXT("SkeletalMesh")));
	SkeletalMesh->SetupAttachment(GetRootComponent());
}

void ASimpleDoor::InteractRequest_Implementation(AEGC_Character* InteractingCharacter)
{
	UE_LOG(LogInteractables, Warning, TEXT("Interact"));
	bIsOpen = !bIsOpen;
}