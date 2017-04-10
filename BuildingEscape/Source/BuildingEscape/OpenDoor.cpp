

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("#####OpenDoor Component Loaded###########"));

    ActorThatOpens = GetWorld() -> GetFirstPlayerController() -> GetPawn();
}

void UOpenDoor::OpenDoor()
{
    //Find the owning actor
    AActor *Owner = GetOwner();

    //Create the rotator
    FRotator NewRotation = FRotator(0.0f, -60.0f, 0.0f);
    //pitch front back, Yaw circular front back along the hinge point, Vertical Circle

    //Set door rotation
    Owner->SetActorRotation(NewRotation);
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    //Poll the Trigger Volume
    //If the ActorThatOpens is in the volume
    if (PressurePlate -> IsOverlappingActor(ActorThatOpens))
    {
        UE_LOG(LogTemp, Warning, TEXT("Stepped on TriggerPlate"));
        OpenDoor();    
    }    
}

