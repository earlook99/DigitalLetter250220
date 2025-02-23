// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DocentCharacter.h"
#include "Components/SphereComponent.h"
#include "Core/DocentAIController.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"

ADocentCharacter::ADocentCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	DocentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Docent Mesh"));
	DocentMesh->SetupAttachment(RootComponent);

	InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Interaction Sphere"));
	InteractionSphere->SetupAttachment(RootComponent);

	InteractionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void ADocentCharacter::BeginPlay()
{
	Super::BeginPlay();

	AIController = Cast<ADocentAIController>(GetController());

	CurrentState = EDocentState::Wait;

	if (InteractionSphere)
	{
		InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &ADocentCharacter::OnSphereOverlapBegin);
		InteractionSphere->OnComponentEndOverlap.AddDynamic(this, &ADocentCharacter::OnSphereOverlapEnd);
	}
}

void ADocentCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (CurrentState == EDocentState::Moving)
	{
		if (GetCharacterMovement()->IsFalling())
		{
			AddMovementInput(GetActorForwardVector(), 1.0f);
		}
	}
}

void ADocentCharacter::SetDocentState(EDocentState NewState)
{
	CurrentState = NewState;

	FString DebugString;
	switch (CurrentState)
	{
		case EDocentState::Wait:
			DebugString = FString("Wait");
			InteractionSphere->SetGenerateOverlapEvents(true);
			break;
		case EDocentState::Moving:
			DebugString = FString("Moving");
			InteractionSphere->SetGenerateOverlapEvents(false);
			Jump();
			break;
		case EDocentState::Explaining:
			DebugString = FString("Explaining");
			InteractionSphere->SetGenerateOverlapEvents(false);
			break;
		default:
			break;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("New State: %s"), *DebugString);
}

void ADocentCharacter::MoveToDocentPoint(ATargetPoint* DocentPoint)
{
	FAIMoveRequest MoveReq;
	MoveReq.SetGoalActor(DocentPoint);
	MoveReq.SetAcceptanceRadius(50.f);
	MoveReq.SetUsePathfinding(true);
	MoveReq.SetAllowPartialPath(true);

	UE_LOG(LogTemp, Display, TEXT("%s"), *DocentPoint->GetName());
	
	AIController->MoveTo(MoveReq);
}

void ADocentCharacter::NotifyMoveCompleted()
{
	OnDocentMoveCompleted.Broadcast();
}

void ADocentCharacter::OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	OnDocentOverlapChanged.Broadcast(true);
}

void ADocentCharacter::OnSphereOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OnDocentOverlapChanged.Broadcast(false);
}

void ADocentCharacter::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);

	if (GetCharacterMovement()->IsMovingOnGround() && PrevMovementMode == MOVE_Falling && CurrentState == EDocentState::Moving)
	{
		Jump();
	}
}
