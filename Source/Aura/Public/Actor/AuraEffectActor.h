// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"


class UGameplayEffect;

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY() 
	
public:	
	AAuraEffectActor();

protected: // Functions
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToActor(
		AActor* TargetActor,
		TSubclassOf<UGameplayEffect> GameplayEffectClass
	);

protected: // Properties
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	
};
