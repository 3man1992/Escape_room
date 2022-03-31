// Libraries
#include "swivelDoor.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"
#include "UObject/UObjectBaseUtility.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"


// Sets default values for this component's properties
UswivelDoor::UswivelDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts
void UswivelDoor::BeginPlay()
{
	Super::BeginPlay();

	//Protect against null pointers!
	if(!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("Actor: %s  has no pressure plate"), *GetOwner()->GetName());
	}

	// // Open door variable settings
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw = InitialYaw + 90.f;
	ClosedYaw = InitialYaw - 90.f;

	//
	ActorThatOpen = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UswivelDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Set a timer
	float Time = GetWorld()->GetTimeSeconds();
	// UE_LOG(LogTemp, Warning, TEXT("Time %f"), Time);

	//Open the door // The first clause protects again null pointers
	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpen))
	{
		OpenDoor(DeltaTime);
	}

	else
	{
		CloseDoor(DeltaTime);
	}
}

void UswivelDoor::OpenDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, DeltaTime * 1.f);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

	//Print out current yaw and actor rotation information - Test log
	// UE_LOG(LogTemp, Warning, TEXT("Actor rotation information %s"), *GetOwner()->GetActorRotation().ToString());
	// UE_LOG(LogTemp, Warning, TEXT("Hello, here is the yaw %f"), GetOwner()->GetActorRotation().Yaw);

}

void UswivelDoor::CloseDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaTime * 0.2f);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

	//Print out current yaw and actor rotation information - Test log
	// UE_LOG(LogTemp, Warning, TEXT("Actor rotation information %s"), *GetOwner()->GetActorRotation().ToString());
	// UE_LOG(LogTemp, Warning, TEXT("Hello, here is the yaw %f"), GetOwner()->GetActorRotation().Yaw);

}

