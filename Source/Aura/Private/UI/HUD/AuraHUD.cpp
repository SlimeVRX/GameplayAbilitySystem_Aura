// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(
			this,
			OverlayWidgetControllerClass
		);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		return OverlayWidgetController;
	}

	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	if (OverlayWidgetClass == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT(
			"Overlay Widget Class uninitialized, pleased fill out BP_AuraHUD"
		));
	}

	if (OverlayWidgetControllerClass == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT(
			"Overlay Widget Controller Class uninitialized, pleased fill out BP_AuraHUD"
		));
	}

	if (OverlayWidgetClass)
	{
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
		if (Widget)
		{
			OverlayWidget = Cast<UAuraUserWidget>(Widget);

			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

			OverlayWidget->SetWidgetController(WidgetController);

			Widget->AddToViewport();
		}
	}
}
