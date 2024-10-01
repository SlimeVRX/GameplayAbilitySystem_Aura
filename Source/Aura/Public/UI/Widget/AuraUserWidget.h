// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()

public: // Functions
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

public: // Properties
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected: // Functions
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();


	
	
	
	
};
