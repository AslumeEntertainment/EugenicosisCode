// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EGC_GameModeBase.generated.h"

class AEGC_Character;

UCLASS()
class EUGENICOSISCODE_API AEGC_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

	bool bIsPaused = false;

	UPROPERTY(EditAnywhere, Category = GameStart)
	TSubclassOf<AEGC_Character> CharacterClass;

	UPROPERTY(EditAnywhere, Category = GameStart)
	FVector CharacterStartLocation;

	UPROPERTY(EditAnywhere, Category = GameStart)
	FRotator CharacterStartRotation;

public:

	UFUNCTION()
	void PauseGame();

};
