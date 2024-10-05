// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	// Lam the nao gui thong tin ve effect nay hien thi tren UI
	FGameplayTagContainer EffectTags;
	EffectSpec.GetAllAssetTags(EffectTags);
	for (FGameplayTag EffectTag : EffectTags)
	{
		//TODO: Broadcast the tag to the Widget Controller
		UE_LOG(LogTemp, Warning, TEXT("Effect Tag: %s"), *EffectTag.ToString());
		if (GEngine) 
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Effect Tag: %s"), *EffectTag.ToString()));
		}
	}
}
