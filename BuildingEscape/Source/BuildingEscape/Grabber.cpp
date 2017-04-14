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
	if (PhysicsHandle)
	{
		//PHandle is found
	}
	else
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
		UE_LOG(LogTemp, Warning, TEXT("Input Component Found"));
		
		//Bind the input axis
		InputComponent -> BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent -> BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner() -> GetName());
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Pressed"));

	//LINE TRACE and see if we reach any actors with physics body collision channel set
	GetFirstPhysicsBodyInReach();

	//If we hit something then attach a physics handle
	//TODO attach physics handle
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Released"));
	//TODO Release physics handle
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//if physics handle is attached 
		//move the object we are holding
}



//Return hit for first physics body in reach
FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
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
	return Hit;
}