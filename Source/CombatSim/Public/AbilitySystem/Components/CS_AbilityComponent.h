// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbility.h"
#include "CS_AbilityComponent.generated.h"

/**
 * 
 */
UCLASS()
class COMBATSIM_API UCS_AbilityComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere)
		TSubclassOf<UGameplayAbility> debugAbility;
};
