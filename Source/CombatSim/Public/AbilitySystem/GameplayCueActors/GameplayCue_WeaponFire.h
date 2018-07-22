// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Actor.h"
#include "GameplayCue_WeaponFire.generated.h"

/**
 * 
 */
UCLASS()
class COMBATSIM_API AGameplayCue_WeaponFire : public AGameplayCueNotify_Actor
{
	GENERATED_BODY()
	
	
public:
	virtual bool OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;

};
