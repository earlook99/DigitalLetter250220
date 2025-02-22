// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/PlayerCharacterController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "Character/PlayerCharacter.h"

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APlayerCharacter>(GetPawn());

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void APlayerCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComp->BindAction(JumpAction, ETriggerEvent::Started, this, &APlayerCharacterController::JumpControl);
		EnhancedInputComp->BindAction(JumpAction, ETriggerEvent::Completed, this, &APlayerCharacterController::JumpStopControl);
		EnhancedInputComp->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacterController::MoveControl);
		EnhancedInputComp->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacterController::LookControl);
		EnhancedInputComp->BindAction(InteractAction, ETriggerEvent::Started, this, &APlayerCharacterController::InteractControl);
	}
}

void APlayerCharacterController::JumpControl(const FInputActionValue& Value)
{
	if (PlayerCharacter) PlayerCharacter->Jump();
}

void APlayerCharacterController::JumpStopControl(const FInputActionValue& Value)
{
	if (PlayerCharacter) PlayerCharacter->StopJumping();
}

void APlayerCharacterController::MoveControl(const FInputActionValue& Value)
{
	if (PlayerCharacter)
	{
		FVector2D MovementVector = Value.Get<FVector2D>();
		PlayerCharacter->Move(MovementVector);
	}
}

void APlayerCharacterController::LookControl(const FInputActionValue& Value)
{
	if (PlayerCharacter)
	{
		FVector2D LookAxisVector = Value.Get<FVector2D>();
		PlayerCharacter->Look(LookAxisVector);
	}
}

void APlayerCharacterController::InteractControl(const FInputActionValue& Value)
{
	if (PlayerCharacter) PlayerCharacter->Interact();
}
