// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SoundEmitterComponent.h"
#include "Perception/AISense_Hearing.h"

USoundEmitterComponent::USoundEmitterComponent()
{
	OnAudioPlaybackPercent.AddDynamic(this, &USoundEmitterComponent::OnSoundPlayed);
}

void USoundEmitterComponent::OnSoundPlayed(const USoundWave* SoundWave, const float PlaybackPercent)
{
	UAISense_Hearing::ReportNoiseEvent(GetWorld(), GetOwner()->GetActorLocation(), 1, GetOwner(), Sound->MaxDistance);

	float OutEnvelopeData;
	if (GetCookedEnvelopeData(OutEnvelopeData))
	{
		OnAmplitudeEnvelopeDataUpdated.ExecuteIfBound(OutEnvelopeData);
	}

	return;
}


