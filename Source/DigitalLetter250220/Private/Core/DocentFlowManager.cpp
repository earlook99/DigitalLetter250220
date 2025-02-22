// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/DocentFlowManager.h"

#include "Character/DocentCharacter.h"
#include "Character/PlayerCharacter.h"

// Sets default values
ADocentFlowManager::ADocentFlowManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADocentFlowManager::BeginPlay()
{
	Super::BeginPlay();

	if (DocentCharacter)
	{
		DocentCharacter->OnDocentMoveCompleted.AddDynamic(this, &ADocentFlowManager::HandleDocentMoveCompleted);
		DocentCharacter->OnDocentOverlapChanged.AddDynamic(this, &ADocentFlowManager::HandleDocentOverlapChanged);
	}
}

// Called every frame
void ADocentFlowManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADocentFlowManager::HandleDocentMoveCompleted()
{
	DocentPointIndex++;
	if (DocentPointIndex < DocentPoints.Num())
	{
		DocentCharacter->MoveToDocentPoint(DocentPoints[DocentPointIndex]);
	}
	else
	{
		// TODO: Tour End
	}
}

void ADocentFlowManager::HandleDocentOverlapChanged(bool bIsOverlapping)
{
	PlayerCharacter->AllowDocentInteraction(bIsOverlapping);
}

