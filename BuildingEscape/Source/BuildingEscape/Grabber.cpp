// Copyright Gaurav Sahni 2017.

#include "BuildingEscape.h"
#include "Grabber.h"
#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("Grabber component Reporting for duty"));

	//Looking for attached Physics Handle
	PhysicsHandle = GetOwner() -> FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle)
	{
		//PHandle is found
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *GetOwner() -> GetName());
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Get Player Viewpoint this Tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld() -> GetFirstPlayerController() -> GetPlayerViewPoint(
												OUT PlayerViewPointLocation, 
												OUT PlayerViewPointRotation
												);
	//Log the Player Location and Rotation
	//UE_LOG(LogTemp, Warning, TEXT("Location %s, Position %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());
	
	//Vector that tells players Reach of hands
	FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);

	//Draw a red trace in the world to visualize
    DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255,0,0),
		false,
		0.f,
		0.f,
		10.f
	);

	//Setup Query Params -- See the documentation here please!!
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
    
	//Line Trace (AKA Ray-cast) out to reach distance
	FHitResult Hit;
	GetWorld()-> LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	//See what we hit
	AActor* ActorHit = Hit.GetActor();
	if(ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(ActorHit->GetName()));
	} 
}

