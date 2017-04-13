

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

    //Gets the Asset to which this script component is attached to. 
    Owner = GetOwner();

    //Gets the Default Pawn
    ActorThatOpens = GetWorld() -> GetFirstPlayerController() -> GetPawn();
}

void UOpenDoor::OpenDoor()
{
   //Set door rotation
    Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}

void UOpenDoor::CloseDoor()
{
    //Set door rotation
    Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    //Poll the Trigger Volume
    //If the ActorThatOpens is in the volume
    if (PressurePlate -> IsOverlappingActor(ActorThatOpens))
    {
        //UE_LOG(LogTemp, Warning, TEXT("Stepped on TriggerPlate"));
        OpenDoor();    
        LastDoorOpenTime = GetWorld()->GetTimeSeconds();
    }  

    //Check if it is time to close the Door
    if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
    {
       CloseDoor(); 
    }  
}

