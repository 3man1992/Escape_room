// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "grapper.h"

#define OUT //does nothing

// Sets default values for this component's properties
Ugrapper::Ugrapper()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void Ugrapper::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Error, TEXT("Has to work"));

	//Check for physics handle
	FindPhysicsHandle();

	UE_LOG(LogTemp, Error, TEXT("Log1"));

	//Check for input
	SetupInputComponent();
}

//When the graber key binding is pressed
void Ugrapper::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("GRabber press"));

	// Get players viewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation, 
		OUT PlayerViewPointRotation
	);

	//log for test position
	// UE_LOG(LogTemp, Warning, TEXT("Location is: %s"), *PlayerViewPointLocation.ToString());
	// UE_LOG(LogTemp, Warning, TEXT("Rotation is: %s"), *PlayerViewPointRotation.ToString());

	//Create reach vector
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach; //vector makes it a unit of 1

	//only ray cast when grabber pressed
	FHitResult HitResult = GetFirstPhysicsBodyInReach();

	//if physics handle attached
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	if (HitResult.GetActor())
	{
		PhysicsHandle->GrabComponentAtLocation
		(
			ComponentToGrab,
			NAME_None,
			LineTraceEnd
		);
	}
	//move object


	//Reach any physcs body with a collison channel

	//Grab physics handle
}

//When the graber key is released
void Ugrapper::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber released"));

	//Release physics handle
	PhysicsHandle->ReleaseComponent();
}

//Setup input key binding
void Ugrapper::SetupInputComponent()
{
	UE_LOG(LogTemp, Error, TEXT("Log2"));
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Input found on component %s"), *GetOwner()->GetName());
		InputComponent->BindAction("Grab", IE_Pressed, this, &Ugrapper::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &Ugrapper::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No input found on component %s"), *GetOwner()->GetName());
	}
}

//Ensure the object has physics
void Ugrapper::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		//physics handle is found
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No physics found on component %s"), *GetOwner()->GetName());
	}
}

// Called every frame
void Ugrapper::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UE_LOG(LogTemp, Error, TEXT("Has to work"));



		// Get players viewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation, 
		OUT PlayerViewPointRotation
	);

	//log for test position
	// UE_LOG(LogTemp, Warning, TEXT("Location is: %s"), *PlayerViewPointLocation.ToString());
	// UE_LOG(LogTemp, Warning, TEXT("Rotation is: %s"), *PlayerViewPointRotation.ToString());

	//Create reach vector
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach; //vector makes it a unit of 1


	//If physics handle grapped
	//Move object we are holding
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}



}

//Comented out for now
// void Ugrapper::DrawDebugLine(FVector PlayerViewPointLocation, FVector LineTraceEnd)
// {
// 	DrawDebugLine(
// 		GetWorld(),
// 		PlayerViewPointLocation,
// 		LineTraceEnd,
// 		FColor(0, 255, 0),
// 		false,
// 		0.f,
// 		0,
// 		5.f
// 	);
// }

FHitResult Ugrapper::GetFirstPhysicsBodyInReach() const
{
	// Get players viewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation, 
		OUT PlayerViewPointRotation
	);

	//log for test position
	// UE_LOG(LogTemp, Warning, TEXT("Location is: %s"), *PlayerViewPointLocation.ToString());
	// UE_LOG(LogTemp, Warning, TEXT("Rotation is: %s"), *PlayerViewPointRotation.ToString());

	//Create reach vector
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach; //vector makes it a unit of 1

	//Draw debug line
	//DrawDebugLine(PlayerViewPointLocation, LineTraceEnd)

	// Ray casting
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	//See what is hits
	AActor* ActorHit = Hit.GetActor();

	if(ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line trace has hit %s"), *(ActorHit->GetName()));
	}

	return Hit; 
}


