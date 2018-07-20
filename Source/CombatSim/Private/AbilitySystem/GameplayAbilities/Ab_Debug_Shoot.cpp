// Fill out your copyright notice in the Description page of Project Settings.

#include "Ab_Debug_Shoot.h"




void UAb_Debug_Shoot::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		// Check CommitAbility.   this should default to true;
		if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
		{
			return;
		}
	}

	// Do the stuff.
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 1, FColor::Black, TEXT("Shooting..."));
	}

	UE_LOG(LogTemp, Log, TEXT("Shoot!"));
}
