// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/DocentFlowManager.h"
#include "Character/DocentCharacter.h"
#include "Character/PlayerCharacter.h"
#include "Core/PlayerCharacterController.h"
#include "Data/DocentDialogue.h"
#include "UI/DialogueWidget.h"

// Sets default values
ADocentFlowManager::ADocentFlowManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADocentFlowManager::BeginPlay()
{
	Super::BeginPlay();

	if (DocentCharacter)
	{
		DocentCharacter->OnDocentMoveCompleted.AddDynamic(this, &ADocentFlowManager::HandleDocentMoveCompleted);
		DocentCharacter->OnDocentOverlapChanged.AddDynamic(this, &ADocentFlowManager::HandleDocentOverlapChanged);
		PlayerCharacter->OnPlayerInteracted.AddDynamic(this, &ADocentFlowManager::HandlePlayerInteracted);
	}
}

// Called every frame
void ADocentFlowManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADocentFlowManager::ShowDialogue(const FDocentDialogue& DialogueData)
{
	if (CurrentDialogueWidget)
	{
		CurrentDialogueWidget->RemoveFromParent();
		CurrentDialogueWidget = nullptr;
	}

	if (DialogueWidgetClass)
	{
		CurrentDialogueWidget = CreateWidget<UDialogueWidget>(GetWorld(), DialogueWidgetClass);
		if (CurrentDialogueWidget)
		{
			CurrentDialogueWidget->OnDialogueFinished.AddDynamic(this, &ADocentFlowManager::OnDialogueFinished);

			CurrentDialogueWidget->AddToViewport();

			CurrentDialogueWidget->StartDialogue(DialogueData);

			APlayerCharacterController* PlayerCharacterController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
			if (PlayerCharacterController)
			{
				FInputModeGameAndUI InputMode;
				InputMode.SetWidgetToFocus(CurrentDialogueWidget->TakeWidget());
				InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
				PlayerCharacterController->SetInputMode(InputMode);
				PlayerCharacterController->bShowMouseCursor = true;
			}
		}
	}
}

void ADocentFlowManager::OnDialogueFinished()
{
	if (CurrentDialogueWidget)
	{
		CurrentDialogueWidget->RemoveFromParent();
		CurrentDialogueWidget = nullptr;
	}

	APlayerCharacterController* PlayerCharacterController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
	if (PlayerCharacterController)
	{
		FInputModeGameOnly Mode;
		PlayerCharacterController->SetInputMode(Mode);
		PlayerCharacterController->bShowMouseCursor = false;
	}

	if (DocentPointIndex < DocentPoints.Num() && DocentCharacter)
	{
		DocentCharacter->SetDocentState(EDocentState::Moving);
		DocentCharacter->MoveToDocentPoint(DocentPoints[DocentPointIndex]);
		DocentPointIndex++;
		DocentDialogueIndex++;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tour End"));
	}
}

void ADocentFlowManager::HandleDocentMoveCompleted()
{
	DocentCharacter->SetDocentState(EDocentState::Wait);
}

void ADocentFlowManager::HandleDocentOverlapChanged(bool bIsOverlapping)
{
	PlayerCharacter->AllowDocentInteraction(bIsOverlapping);
}

void ADocentFlowManager::HandlePlayerInteracted()
{
	if (!DocentDialogueTable)
	{
		return;
	}

	static const FString ContextString = FString("DocentDialogueTable");
	
	FString DialogueString = FString("Dialogue_00") + FString::FromInt(DocentDialogueIndex);
	FName RowName = FName(*DialogueString);
	FDocentDialogue* Row = DocentDialogueTable->FindRow<FDocentDialogue>(RowName, ContextString);

	if (Row)
	{
		FDocentDialogue DialogueData = *Row;
		ShowDialogue(DialogueData);

		if (DocentCharacter)
		{
			DocentCharacter->SetDocentState(EDocentState::Explaining);
		}
	}
}

