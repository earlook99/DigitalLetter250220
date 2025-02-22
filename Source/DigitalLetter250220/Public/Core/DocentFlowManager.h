// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DocentFlowManager.generated.h"

class APlayerCharacter;
class ADocentCharacter;
class ATargetPoint;

UCLASS()
class DIGITALLETTER250220_API ADocentFlowManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADocentFlowManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void HandleDocentMoveCompleted();

	UFUNCTION()
	void HandleDocentOverlapChanged(bool bIsOverlapping);
	
	UPROPERTY(EditAnywhere)
	ADocentCharacter* DocentCharacter;

	UPROPERTY(EditAnywhere)
	APlayerCharacter* PlayerCharacter;
	
	UPROPERTY(EditAnywhere)
	TArray<ATargetPoint*> DocentPoints;

	int32 DocentPointIndex = 0;
};
