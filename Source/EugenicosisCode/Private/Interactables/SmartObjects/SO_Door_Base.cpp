// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactables/SmartObjects/SO_Door_Base.h"

#include "SmartObjectSubsystem.h"
#include "SmartObjectRuntime.h" 
#include "SmartObjectComponent.h"
#include "Navigation/NavLinkProxy.h"
#include "Components/ChildActorComponent.h"
#include "EugenicosisCode.h"

// Sets default values
ASO_Door_Base::ASO_Door_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SmartObjectComp = CreateDefaultSubobject<USmartObjectComponent>(FName(TEXT("SmartObjectComp")));
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName(TEXT("SkeletalMesh")));
	NavLink = CreateDefaultSubobject<UChildActorComponent>(FName(TEXT("NavLink")));
	NavLink->SetChildActorClass(ANavLinkProxy::StaticClass());
	SkeletalMesh->SetupAttachment(GetRootComponent());
	NavLink->SetupAttachment(SkeletalMesh);
	SmartObjectComp->SetupAttachment(SkeletalMesh);
}

// Called when the game starts or when spawned
void ASO_Door_Base::BeginPlay()
{
	Super::BeginPlay();
	//NavLink->CreateChildActor();
	ANavLinkProxy* Proxy = Cast<ANavLinkProxy>(NavLink->GetChildActor());
	if (IsValid(Proxy) == false)
	{
		UE_LOG(LogSmartObject, Error, TEXT("ASO_Door_Base::BeginPlay IsValid(Proxy) == false"));
		return;
	}
}

// Called every frame
void ASO_Door_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASO_Door_Base::OnInteraction(AActor* Agent)
{	
	UE_LOG(LogSmartObjects, Warning, TEXT("it somehow works?!"));
}

