// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Character/AuraEnemy.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	if (CursorHit.bBlockingHit)
	{
		LastActor = ThisActor;
		ThisActor = CursorHit.GetActor();

		// Line trace from cursor to actor
		// A. LastActor is null && ThisActor is null
		//		- Do nothing
		// B. LastActor is null && ThisActor is valid
		//		- Call HighlightActor on ThisActor
		// C. LastActor is valid && ThisActor is null
		//		- Call UnhighlightActor on LastActor
		// D. LastActor is valid && ThisActor is valid, but LastActor != ThisActor
		// 		- Call UnhighlightActor on LastActor and HighlightActor on ThisActor
		// E. LastActor is valid && ThisActor is valid, and LastActor == ThisActor
		// 		- Do nothing

		if (LastActor == nullptr) {
			if (ThisActor != nullptr) {
				// Case B
				ThisActor->HighlightActor();
			}
			else 
			{
				// Case A - both are null, do nothing
			}
		}
		else // LastActor is valid
		{
			if (ThisActor == nullptr) {
				// Case C
				LastActor->UnhighlightActor();
			}
			else // both are  valid
			{
				if (LastActor != ThisActor) {
					// Case D
					LastActor->UnhighlightActor();
					ThisActor->HighlightActor();
				}
				else {
					// Case E - both are the same, do nothing
				}
			}
		}
	}
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// GetLocalPlayer
	// ULocalPlayer::GetSubsystem
	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		if (AuraContext)
		{
			Subsystem->AddMappingContext(AuraContext, 0);
		}
		
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	if(EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	}	

}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisValue = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisValue.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisValue.X);
	}
}
