// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
	
public: // Functions
	AAuraEnemy();
	virtual void HighlightActor() override;
	virtual void UnhighlightActor() override;
	
public: // Properties
	UPROPERTY(BluePrintReadOnly)
	bool bHighlighted = false;
	
protected: // Functions
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;

};
