// Fill out your copyright notice in the Description page of Project Settings.

#include "Ab_Debug_Shoot.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"





UAb_Debug_Shoot::UAb_Debug_Shoot()
{
	//this->projectileClassPath = TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonProjectile.FirstPersonProjectile");
	this->projectileClassPath = TEXT("Blueprint'/Game/FirstPersonCPP/Blueprints/FirstPersonProjectile.FirstPersonProjectile'");

	static ConstructorHelpers::FObjectFinder<UBlueprint> projectileFinder(*projectileClassPath);
	if (projectileFinder.Object != NULL) {
		//projectileClass = projectileFinder.Object->GeneratedClass;
	}
	this->InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerExecution;
	//this->projectileClassPath = TEXT("FirstPersonProjectile");
}

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

	if (projectileClass == nullptr)
	{
		LoadProjectileClassReference();
	}

	if (projectileClass != nullptr)
	{
		TArray<UActorComponent*> componentsWithProjectileTag = ActorInfo->AvatarActor->GetComponentsByTag(USceneComponent::StaticClass(), FName("ProjectileOut"));
		

		FTransform projectileSpawnTransform;
		if (componentsWithProjectileTag.Num() > 0)
		{
			if (USceneComponent* firstComponent = Cast<USceneComponent>(componentsWithProjectileTag[0]))
			{
				// Found a scene component with the right tag.
				FTransform componentTransform = firstComponent->GetComponentTransform();
				projectileSpawnTransform = firstComponent->GetComponentTransform();
			}
			else
			{
				// No valid scene component.
				projectileSpawnTransform = ActorInfo->AvatarActor->GetTransform();
			}
		}
		else
		{
			projectileSpawnTransform = ActorInfo->AvatarActor->GetTransform();
		}

		FActorSpawnParameters parameters;
		parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		AActor* projectile = GetWorld()->SpawnActor<AActor>(projectileClass, projectileSpawnTransform, parameters);
		
		UAbilitySystemComponent* ownerComponent = GetAbilitySystemComponentFromActorInfo();

		FGameplayTag fireTag = UGameplayTagsManager::Get().RequestGameplayTag("GameplayCue.Weapon.Fire");
		ownerComponent->ExecuteGameplayCue(fireTag);
	}

}

void UAb_Debug_Shoot::LoadProjectileClassReference()
{
	if (!projectileClassPath.IsEmpty())
	{
		UObject* ClassPackage = ANY_PACKAGE;
		FString fullPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()) + projectileClassPath;
		UClass* Result = FindObject<UClass>(ClassPackage, *fullPath);
		UObject* someObject = StaticLoadObject(UObject::StaticClass(), nullptr, *projectileClassPath);

		UBlueprint* castedBlueprint = Cast<UBlueprint>(someObject);

		if (castedBlueprint && castedBlueprint->GeneratedClass->IsChildOf(AActor::StaticClass()))
		{
			projectileClass = *castedBlueprint->GeneratedClass;
		}
		else
		{
			UClass* someClass = StaticLoadClass(UObject::StaticClass(), nullptr, *projectileClassPath);
		}



		UClass* someClass = StaticLoadClass(UObject::StaticClass(), nullptr, *projectileClassPath);
		
		//UClass* someClass = StaticLoadClass(UObject::StaticClass(), nullptr, *projectileClassPath);

		UClass* someActorClass = StaticLoadClass (AActor::StaticClass(), nullptr, *projectileClassPath);
		//TSubclassOf<AActor> someActorSubclass = *Cast<TSubclassOf<AActor>> (StaticLoadClass(AActor::StaticClass(), nullptr, *projectileClassPath));
		

		TSubclassOf<AActor> subclass = StaticLoadClass(AActor::StaticClass(), this, *fullPath);
		//AActor* loadedActor = Staticload  LoadObject<UBlueprint>(, *projectileClassPath, NULL, LOAD_None, NULL);


		if (subclass != nullptr)
		{
			projectileClass = subclass;
		}

	}
}

