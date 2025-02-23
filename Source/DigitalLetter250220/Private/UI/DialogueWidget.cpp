// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DialogueWidget.h"
#include "Components/TextBlock.h"
#include "Data/DocentDialogue.h"
#include "Kismet/GameplayStatics.h"

void UDialogueWidget::StartDialogue(const FDocentDialogue& InDialogue)
{
	Lines = InDialogue.Lines;
	CurrentLineIndex = 0;

	if (Lines.Num() > 0)
	{
		StartTyping(Lines[0]);
	}
}

void UDialogueWidget::StartTyping(const FDocentLine& Line)
{
	GetWorld()->GetTimerManager().ClearTimer(TypingTimer);

	FullSentence = Line.DialogueText.ToString();
	DisplayedSentence.Empty();
	CurrentCharIndex = 0;
	bLineFullyDisplayed = false;

	if (Line.bPlayExclamation && Line.ExclamationSound)
	{
		UGameplayStatics::PlaySound2D(this, Line.ExclamationSound);
	}

	GetWorld()->GetTimerManager().SetTimer(
		TypingTimer,
		this,
		&UDialogueWidget::TickTyping,
		TypingRate,
		true
	);
}

void UDialogueWidget::TickTyping()
{
	if (CurrentCharIndex >= FullSentence.Len())
	{
		bLineFullyDisplayed = true;
		GetWorld()->GetTimerManager().ClearTimer(TypingTimer);
		return;
	}

	DisplayedSentence.AppendChar(FullSentence[CurrentCharIndex]);
	CurrentCharIndex++;
	UpdateTextDisplay();
}

void UDialogueWidget::SkipTyping()
{
	GetWorld()->GetTimerManager().ClearTimer(TypingTimer);

	DisplayedSentence = FullSentence;
	bLineFullyDisplayed = true;
	UpdateTextDisplay();
}

FReply UDialogueWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	HandleInput();
	return FReply::Handled();
}

FReply UDialogueWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::E)
	{
		HandleInput();
		return FReply::Handled();
	}
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UDialogueWidget::HandleInput()
{
	if (!bLineFullyDisplayed)
	{
		SkipTyping();
	}
	else
	{
		AdvanceLine();
	}
}

void UDialogueWidget::AdvanceLine()
{
	CurrentLineIndex++;
	if (CurrentLineIndex >= Lines.Num())
	{
		OnDialogueFinished.Broadcast();
	}
	else
	{
		StartTyping(Lines[CurrentLineIndex]);
	}
}

void UDialogueWidget::UpdateTextDisplay()
{
	UTextBlock* TextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("DialogueText")));
	if (TextBlock)
	{
		TextBlock->SetText(FText::FromString(DisplayedSentence));
	}
}
