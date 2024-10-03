// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AuraEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
//#include "AbilitySystem/AuraAttributeSet.h"


AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USphereComponent>(TEXT("SceneRoot")));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

}

void AAuraEffectActor::ApplyEffectToActor(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC)
	{
		if (GameplayEffectClass)
		{
			FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
			EffectContextHandle.AddSourceObject(this);
			const FGameplayEffectSpecHandle EffectSpecHandle =
				TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);
			if (EffectSpecHandle.IsValid())
			{
				TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
			}
		}
	}
}


