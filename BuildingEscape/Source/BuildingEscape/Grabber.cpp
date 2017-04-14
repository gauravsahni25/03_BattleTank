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
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandleComponent();
    SetupInputComponent();
}
void UGrabber::FindPhysicsHandleComponent()
{
	//Looking for attached Physics Handle
	PhysicsHandle = GetOwner() -> FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *GetOwner() -> GetName());
	}
}

void UGrabber::SetupInputComponent()
{
	//Looking for attached Physics Handle
	InputComponent = GetOwner() -> FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent -> BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent -> BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner() -> GetName());
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//if physics handle is attached 
	if (PhysicsHandle -> GrabbedComponent)
	{
		//move the object we are holding
		PhysicsHandle-> SetTargetLocation(GetReachLineEnd());
	}
}

void UGrabber::Grab()
{
	//LINE TRACE and see if we reach any actors with physics body collision channel set
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent(); //Gets the mesh in our case
	auto ActorHit = HitResult.GetActor();

	//If we hit something then attach a physics handle
	if (ActorHit)
	{
		// 		UFUNCTION (BlueprintCallable , Category="Physics|Components|PhysicsHandle" )
		// ENGINE_API void GrabComponent
		// (
		//     class UPrimitiveComponent * Component,
		//     FName InBoneName,
		//     FVector GrabLocation,
		//     bool bConstrainRotation
		// )
		PhysicsHandle -> GrabComponent(
			ComponentToGrab,
			NAME_None, //Special Value, Enum for the bones, we used this value because we are not using Bones/ We are using Static Meshes in all cases so far
			ComponentToGrab -> GetOwner() -> GetActorLocation(),
			true // Allow rotation
		);
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Released"));
	PhysicsHandle -> ReleaseComponent();
}

//Return hit for first physics body in reach
const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	//Line Trace (AKA Ray-cast) out to reach distance
	FHitResult HitResult;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	GetWorld()-> LineTraceSingleByObjectType(  // vs LineTraceSingleByChannel // we are using this one because it is easy to sort by PhysicsObject Body here
		OUT HitResult,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	//See what we hit
	AActor* ActorHit = HitResult.GetActor();
	if(ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(ActorHit->GetName()));
	} 
	return HitResult;
}

FVector UGrabber::GetReachLineStart()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld() -> GetFirstPlayerController() -> GetPlayerViewPoint(
												OUT PlayerViewPointLocation, 
												OUT PlayerViewPointRotation
												);
	return PlayerViewPointLocation;
}

FVector UGrabber::GetReachLineEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld() -> GetFirstPlayerController() -> GetPlayerViewPoint(
												OUT PlayerViewPointLocation, 
												OUT PlayerViewPointRotation
												);
	return PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);
}