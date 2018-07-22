// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayCue_WeaponFire.h"


bool AGameplayCue_WeaponFire::OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	// Don't check the tag, as we will assume we have the correct tags already.


	// This copy is necessary because using Effectcontext directly causes compile issues for some reason.
	//FGameplayEffectContextHandle effectContext = Parameters.EffectContext;
	//Parameters.

	//const TArray<TWeakObjectPtr<AActor>> affectedActors =  Parameters.EffectContext.GetActors();
	TWeakObjectPtr<AActor> instigator = Parameters.Instigator;
	
	if (GEngine)
	{
		
		FString displayString = FString::Printf(TEXT("Gameplay cue for tag %s.  Instigator: %s.  Target: %s"),
			*Parameters.MatchedTagName.ToString(),
			instigator != nullptr ? *instigator->GetName() : TEXT("NONE"),
			MyTarget != nullptr ? *MyTarget->GetName() : TEXT("NO ACTORS")
		);
		

		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, *displayString);
	}
	

	return true;
}
