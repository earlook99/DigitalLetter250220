#pragma once

#include "CoreMinimal.h"
#include "DocentLine.generated.h"

USTRUCT(BlueprintType)
struct FDocentLine
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue")
	int32 LineID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue")
	FText DialogueText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue")
	bool bPlayExclamation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue")
	USoundBase* ExclamationSound;
};