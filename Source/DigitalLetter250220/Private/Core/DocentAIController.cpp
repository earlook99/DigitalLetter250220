// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/DocentAIController.h"

#include "Character/DocentCharacter.h"

void ADocentAIController::BeginPlay()
{
	Super::BeginPlay();

	DocentCharacter = Cast<ADocentCharacter>(GetPawn());
}

void ADocentAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	if (DocentCharacter)
	{
		DocentCharacter->NotifyMoveCompleted();
	}
}
