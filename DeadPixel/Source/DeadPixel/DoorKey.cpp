// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorKey.h"


// Sets default values for this component's properties
UDoorKey::UDoorKey()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorKey::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDoorKey::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int UDoorKey::GetID() const
{
	return KeyId;
}

