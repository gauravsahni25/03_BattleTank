

#include "BuildingEscape.h"
#include "PositionReport.h"


// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();
    FString name =  GetOwner()->GetName();
    FString position = GetOwner()->GetTransform().GetLocation().ToString();
	//The *name and *position in the code below is wierd, here it is not pointer *name, * is actually
	//an overloaded operator that this UE_LOG macro requires here
    UE_LOG(LogTemp, Warning, TEXT("%s is at %s"), *name, *position);
	// ...
	
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

