// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamemodes/EGC_TitleGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"

void AEGC_TitleGameMode::BeginPlay()
{
	Super::BeginPlay();

	SwitchCamera(DefaultCameraTag);
}

void AEGC_TitleGameMode::SwitchCamera(FName CameraTag)
{
	APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!IsValid(PlayerController)) {
		return;
	}

	TArray<AActor*> CamerasInLevel;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), CamerasInLevel);

	for (AActor* Actor : CamerasInLevel)
	{
		ACameraActor* CameraActor = Cast<ACameraActor>(Actor);

		if (CameraActor->ActorHasTag(CameraTag)) 
		{
			PlayerController->SetViewTargetWithBlend(CameraActor, 0, EViewTargetBlendFunction::VTBlend_Linear);
		}
	}
}

void AEGC_TitleGameMode::StartGame()
{
}

void AEGC_TitleGameMode::QuitGame()
{
	APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!IsValid(PlayerController)) {
		return;
	}

	PlayerController->ConsoleCommand("quit");
}
