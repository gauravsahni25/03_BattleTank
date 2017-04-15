// Copyright Gaurav Sahni 2017.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    UPROPERTY(EditAnywhere)
    float OpenAngle = -90.0f;
    
    UPROPERTY(EditAnywhere)
    ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
    float DoorCloseDelay = 1.0f;

	float LastDoorOpenTime;
    AActor* Owner; // The owning Actor
    
    void OpenDoor();
	void CloseDoor();
	//Return total mass in kg
	float GetTotalMassOfActorOnPlate();	
};
