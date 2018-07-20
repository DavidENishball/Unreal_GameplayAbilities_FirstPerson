// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Ab_Debug_Shoot.generated.h"

/**
 * 
 */
UCLASS()
class COMBATSIM_API UAb_Debug_Shoot : public UGameplayAbility
{
	GENERATED_BODY()


	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
};
