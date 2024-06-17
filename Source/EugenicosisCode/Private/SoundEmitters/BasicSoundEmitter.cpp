// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundEmitters/BasicSoundEmitter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SoundEmitterComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Hearing.h"

// Sets default values
ABasicSoundEmitter::ABasicSoundEmitter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(GetRootComponent());

	SoundEmitterComponent = CreateDefaultSubobject<USoundEmitterComponent>(TEXT("SoundEmitter"));
	SoundEmitterComponent->SetupAttachment(StaticMeshComponent);

	StimulusSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("StimulusSource"));
	StimulusSourceComponent->RegisterForSense(TSubclassOf<UAISense_Hearing>());
	StimulusSourceComponent->RegisterWithPerceptionSystem();
}

void ABasicSoundEmitter::PlaySound()
{
	SoundEmitterComponent->Play();
}

// Called when the game starts or when spawned
void ABasicSoundEmitter::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(SoundReplayTimer, this, &ABasicSoundEmitter::PlaySound, 5, true, InitialTime);
}

// Called every frame
void ABasicSoundEmitter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

