// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DocentAIController.generated.h"

class ADocentCharacter;
/**
 * 
 */
UCLASS()
class DIGITALLETTER250220_API ADocentAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

private:
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	UPROPERTY()
	ADocentCharacter* DocentCharacter;
};
