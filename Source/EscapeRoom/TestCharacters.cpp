// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCharacters.h"

// Sets default values
ATestCharacters::ATestCharacters()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestCharacters::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestCharacters::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestCharacters::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

