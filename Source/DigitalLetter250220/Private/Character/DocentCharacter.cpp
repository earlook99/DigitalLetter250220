// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DocentCharacter.h"

// Sets default values
ADocentCharacter::ADocentCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADocentCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADocentCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADocentCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

