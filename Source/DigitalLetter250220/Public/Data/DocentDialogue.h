#pragma once

#include "CoreMinimal.h"
#include "DocentLine.h"
#include "DocentDialogue.generated.h"

USTRUCT(BlueprintType)
struct FDocentDialogue : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue")
	int32 DialogueID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue")
	TArray<FDocentLine> Lines;
};