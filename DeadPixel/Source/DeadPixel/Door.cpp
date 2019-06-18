// Fill out your copyright notice in the Description page of Project Settings.

#include "Door.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UDoor::UDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoor::BeginPlay()
{
	Super::BeginPlay();

	// ...


}


// Called every frame
void UDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
	if (IsLocked())
	{
		CloseDoor();
	}
}

bool UDoor::IsLocked() const
{
	return LockStatus;
}

void UDoor::OpenDoor()
{
	if (LockStatus == false) {
		//Find the owning actor
		AActor* Owner = GetOwner();

		//Create a rotator
		FRotator NewRotation = FRotator(0.f, -90.f, 0.f);

		//Set the door rotation
		Owner->SetActorRotation(NewRotation);
	}
}

void UDoor::CloseDoor()
{
	
	//Find the owning actor
	AActor* Owner = GetOwner();

	//Create a rotator
	FRotator NewRotation = FRotator(0.f, -90.f, 0.f);
	//Set the door rotation
	Owner->SetActorRotation(FRotator(0.f, 0, 0.f));
}
void UDoor::UnlockDoor()
{
	LockStatus = false;
}
void UDoor::UnlockDoor(UDoorKey *Key)
{
	if (Key->GetID() == KeyIdToUnlock)
	{
		LockStatus = false;
		UE_LOG(LogTemp, Error, TEXT("DoorUnlocked"));
	}
}
