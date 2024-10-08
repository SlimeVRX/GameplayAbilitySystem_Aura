// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AuraGameplayTags.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
	// GameplayTags.Attributes_Secondary_Armor.ToString();
	// print "Tag: Attributes"
	GEngine->AddOnScreenDebugMessage(
		-1,
		5.f,
		FColor::Red,
		FString::Printf(TEXT("Tag: %s"), *GameplayTags.Attributes_Secondary_Armor.ToString())
	);
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	// Lam the nao gui thong tin ve effect nay hien thi tren UI
	FGameplayTagContainer EffectTags;
	EffectSpec.GetAllAssetTags(EffectTags);

	EffectAssetTags.Broadcast(EffectTags);

}
