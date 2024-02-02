#include "Interactables/SmartObjects/SimpleDoor.h"

void ASimpleDoor::UseSmartObject(AActor* Agent)
{
	
	Super::UseSmartObject(Agent);
	bIsOpen = !bIsOpen;
}
