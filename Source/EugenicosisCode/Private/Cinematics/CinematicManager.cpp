// Fill out your copyright notice in the Description page of Project Settings.


#include "Cinematics/CinematicManager.h"

#include "Cinematics/CinematicTrigger.h"

#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"

// Sets default values
ACinematicManager::ACinematicManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ACinematicManager::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> CinematicTriggers;
	Cinematics.GenerateKeyArray(CinematicTriggers);

	for (AActor* Actor : CinematicTriggers)
	{

		ICinematicTrigger* Trigger = Cast<ICinematicTrigger>(Actor);
		if (Trigger == nullptr)
		{
			UE_LOG(LogCinematics, Error, TEXT("From Cinematics Map - CinematicTrigger: %s does not implement ICinematicTrigger"));
			continue;
		}

		Trigger->Execute_AttachToCinematicManager(Actor, this);
	}
}

void ACinematicManager::PlaySequence(AActor* Initiator, int ID)
{
	UE_LOG(LogTemp, Warning, TEXT("Fana go"));


	UWorld* World = GetWorld();
	if (IsValid(World) == false)
	{
		UE_LOG(LogCinematics, Error, TEXT("ACinematicManager::PlaySequence IsValid(World) == false"));
		return;
	}

	FPerActorCinematics* PerInitiatorCinematicsPtr = Cinematics.Find(Initiator);
	if (PerInitiatorCinematicsPtr == nullptr)
	{
		UE_LOG(LogCinematics, Error, TEXT("ACinematicManager::PlaySequence PerInitiatorCinematicsPtr == nullptr"));
		return;
	}

	TMap<int, ULevelSequence*> PerInitiatorCinematics = (*PerInitiatorCinematicsPtr).Cinematics;
	FMovieSceneSequencePlaybackSettings Settings = (*PerInitiatorCinematicsPtr).Settings;
	ULevelSequence** LevelSequencePtr = PerInitiatorCinematics.Find(ID);
	if (LevelSequencePtr == nullptr)
	{
		UE_LOG(LogCinematics, Error, TEXT("ACinematicManager::PlaySequence LevelSequencePtr == nullptr - No such Cinematic ID: %d"), ID);
		return;
	}

	ULevelSequence* LevelSequence = *LevelSequencePtr;
	ALevelSequenceActor* OutActor;
	Player = ULevelSequencePlayer::CreateLevelSequencePlayer(World, LevelSequence, Settings, OutActor);
	Player->Play();
}


