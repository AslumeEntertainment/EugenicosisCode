// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "SoundEmitterComponent.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FAmplitudeEnvelopeDataSignature, float, EnvelopeData, AActor*, SoundEmitter);

UCLASS()
class EUGENICOSISCODE_API USoundEmitterComponent : public UAudioComponent
{
	GENERATED_BODY()
	
public:
	USoundEmitterComponent();

	FAmplitudeEnvelopeDataSignature OnAmplitudeEnvelopeDataUpdated;

protected:

	UFUNCTION()
	void OnSoundPlayed(const USoundWave* SoundWave, const float PlaybackPercent);

	UFUNCTION()
	void OnSoundEnded();

};
