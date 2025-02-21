#pragma once

#include "CoreMinimal.h"
#include "DocentDialogue.generated.h"

USTRUCT(BlueprintType)
struct FDocentDialogue
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	int32 DialogueID;

	UPROPERTY(EditAnywhere)
	FText DialogueText;

	UPROPERTY(EditAnywhere)
	bool bPlayExclamation;

	UPROPERTY(EditAnywhere)
	USoundBase* ExclamationSound;
};