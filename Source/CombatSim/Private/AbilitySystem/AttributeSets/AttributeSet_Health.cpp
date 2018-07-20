// Fill out your copyright notice in the Description page of Project Settings.

#include "AttributeSet_Health.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"
#include "GameplayEffectExtension.h"




void UAttributeSet_Health::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data)
{
	static UProperty* HealthProperty = FindFieldChecked<UProperty>(UAttributeSet_Health::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSet_Health, Health));
	static UProperty* DamageProperty = FindFieldChecked<UProperty>(UAttributeSet_Health::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSet_Health, Damage));


	//UProperty* ModifiedProperty = Data.EvaluatedData.Attribute.GetUProperty();
	//FGameplayAttribute testAttribute;

	// Example:
	FGameplayAttributeData* attributeDataChanged = Data.EvaluatedData.Attribute.GetGameplayAttributeData(this);

	// What property was modified?
	if (attributeDataChanged == &Damage)
	{
		Health.SetCurrentValue(Health.GetCurrentValue() - Damage.GetCurrentValue());
		//Health -= Damage;
		Damage.SetCurrentValue(0);
	}
	else if (attributeDataChanged == &Health)
	{
		if (Health.GetCurrentValue() <= 0)
		{
			UE_LOG(LogTemp, Log, TEXT("DEATH"));
		}
	}
}
