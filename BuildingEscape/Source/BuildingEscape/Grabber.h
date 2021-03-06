// Copyright Gaurav Sahni 2017.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	//How far ahead of player can we reach in cms	
	float Reach = 100.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;
	
	//Ray-cast and grab what is in reach
	void Grab();

	//Called when Grab is Released
	void Release();

	//Find (assumed) attached physics handle
	void FindPhysicsHandleComponent();

	//Setup (assumed) attached Input Component
	void SetupInputComponent();

	//Return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();

	//Return current start of Reach Line	
	FVector GetReachLineStart();

	//Return current end of Reach Line	
	FVector GetReachLineEnd();
};
