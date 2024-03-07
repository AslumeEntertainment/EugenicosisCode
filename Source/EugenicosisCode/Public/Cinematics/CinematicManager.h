// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "MovieSceneSequencePlayer.h"
#include "CinematicManager.generated.h"

class ICinematicTrigger;
class ULevelSequence;
class ULevelSequencePlayer;
struct FMovieSceneSequencePlaybackSettings;

USTRUCT()
struct FPerActorCinematics
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	TMap<int, ULevelSequence*> Cinematics;

	UPROPERTY(EditAnywhere)
	FMovieSceneSequencePlaybackSettings Settings;
};

UCLASS()
class EUGENICOSISCODE_API ACinematicManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACinematicManager();

protected:

	UPROPERTY(EditAnywhere)
	TMap<AActor*, FPerActorCinematics> Cinematics;

	UPROPERTY()
	ULevelSequencePlayer* Player;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION()
	void PlaySequence(AActor* Initiator, int ID);
};
