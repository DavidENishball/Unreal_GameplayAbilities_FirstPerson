// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayCue_WeaponFire.h"
#include "CombatSimCharacter.h"
#include "Kismet/GameplayStatics.h"



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



	// Play effects
	if (ACombatSimCharacter* character = Cast<ACombatSimCharacter>(MyTarget))
	{
		// try and play the sound if specified
		if (character->FireSound != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(character, character->FireSound, character->GetActorLocation());
		}

		// try and play a firing animation if specified
		if (character->FireAnimation != NULL)
		{
			// Get the animation object for the arms mesh
			// need to search since it's not directly available.


			TArray<UActorComponent *> componentsByTag = character->GetComponentsByTag(USkeletalMeshComponent::StaticClass(), FName("GameplayCue.Weapon.Fire"));
			for (UActorComponent* c : componentsByTag)
			{
				USkeletalMeshComponent* skeletalMeshComponent = Cast<USkeletalMeshComponent>(c);
				if (!skeletalMeshComponent)
				{
					continue;
				}
				if (UAnimInstance* AnimInstance = skeletalMeshComponent->GetAnimInstance())
				{
					AnimInstance->Montage_Play(character->FireAnimation, 1.f);
				}
			}
		}
	}
	

	return true;
}
