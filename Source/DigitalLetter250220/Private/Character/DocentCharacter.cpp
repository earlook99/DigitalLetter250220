// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DocentCharacter.h"
#include "Components/SphereComponent.h"
#include "Core/DocentAIController.h"
#include "Engine/TargetPoint.h"

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

void ADocentCharacter::SetDocentState(EDocentState NewState)
{
	CurrentState = NewState;
}

void ADocentCharacter::MoveToDocentPoint(ATargetPoint* DocentPoint)
{
	AIController->MoveToActor(DocentPoint);
}

void ADocentCharacter::NotifyMoveCompleted()
{
	OnDocentMoveCompleted.Broadcast();
}

void ADocentCharacter::OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("Overlap Begin with %s"), *OtherActor->GetName());

	OnDocentOverlapChanged.Broadcast(true);
}

void ADocentCharacter::OnSphereOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Log, TEXT("Overlap End with %s"), *OtherActor->GetName());

	OnDocentOverlapChanged.Broadcast(false);
}