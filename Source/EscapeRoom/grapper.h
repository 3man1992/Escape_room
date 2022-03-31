// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "grapper.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOM_API Ugrapper : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	Ugrapper();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


private:
	//Member variables
	UPROPERTY(EditAnywhere)
	float Reach = 300.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr; //prevent crash
	UInputComponent* InputComponent = nullptr; //prevent crash

	void Grab();
	void Release();
	void FindPhysicsHandle();
	void SetupInputComponent();
	// void DrawDebugLine(FVector PlayerViewPointLocation, FVector LineTraceEnd);

	//REturn the first Actor within reach with physics body
	FHitResult GetFirstPhysicsBodyInReach() const;

	//return line trace end
	FVector ReturnLineTraceEnd() const;

};
