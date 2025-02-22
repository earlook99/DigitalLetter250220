// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DocentCharacter.generated.h"

class ADocentAIController;
class ATargetPoint;
class USphereComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDocentMoveCompleted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDocentOverlapChanged, bool, bIsOverlapping);

UENUM(BlueprintType)
enum class EDocentState : uint8
{
	Wait		UMETA(DisplayName = "Wait"),
	Moving		UMETA(DisplayName = "Moving"),
	Explaining	UMETA(DisplayName = "Explaining")
};

UCLASS()
class DIGITALLETTER250220_API ADocentCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADocentCharacter();

	virtual void BeginPlay() override;

	void SetDocentState(EDocentState NewState);

	void MoveToDocentPoint(ATargetPoint* DocentPoint);

	void NotifyMoveCompleted();

	FOnDocentMoveCompleted OnDocentMoveCompleted;

	FOnDocentOverlapChanged OnDocentOverlapChanged;

private:
	EDocentState CurrentState;
	
	UPROPERTY(VisibleAnywhere)
	USphereComponent* InteractionSphere;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* DocentMesh;

	UPROPERTY()
	ADocentAIController* AIController;

	UFUNCTION()
	void OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnSphereOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
