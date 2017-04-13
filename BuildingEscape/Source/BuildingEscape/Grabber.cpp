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
	//UE_LOG(LogTemp, Warning, TEXT("Location %s, Position %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());
	
	FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * 100);

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
	//Ray-cast out to reach distance

	//See what we hit
}

