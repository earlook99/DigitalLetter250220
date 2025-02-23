// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.generated.h"

struct FDocentLine;
struct FDocentDialogue;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueFinished);
/**
 * 
 */
UCLASS()
class DIGITALLETTER250220_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void StartDialogue(const FDocentDialogue& InDialogue);

	UPROPERTY(BlueprintAssignable)
	FOnDialogueFinished OnDialogueFinished;

protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

private:
	TArray<FDocentLine> Lines;
	int32 CurrentLineIndex;
	
	FString FullSentence;
	FString DisplayedSentence;
	int32 CurrentCharIndex;
	bool bLineFullyDisplayed;

	FTimerHandle TypingTimer;
	
	UPROPERTY(EditAnywhere)
	float TypingRate = 0.04f;
	
	void StartTyping(const FDocentLine& Line);
	void TickTyping();
	void HandleInput();
	void SkipTyping();
	void AdvanceLine();
	void UpdateTextDisplay();
};
