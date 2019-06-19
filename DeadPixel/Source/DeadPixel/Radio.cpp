// Fill out your copyright notice in the Description page of Project Settings.

#include "Radio.h"
#include "Engine/World.h"
#include "Battery.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Public/DrawDebugHelpers.h"
#include "GrabObject.h"
// Sets default values for this component's properties
URadio::URadio()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URadio::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URadio::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Anteneas = AntenaControler->FindComponentByClass<UPedestal>();	
	// ...
	if (BatteryPlaced == false)
	{
		if (Battery)

		{
			Battery->SetActorHiddenInGame(true);
		}
	}
	else
	{
		if (Battery)

		{
			Battery->SetActorHiddenInGame(false);
		}
	}


			AntenasPlaced = Anteneas->AntenasPlaced();

}

void URadio::ActivateRadio()
{

	if (AntenasPlaced == true) {
		if (BatteryPlaced == true)
		{
			UE_LOG(LogTemp, Error, TEXT("YOU WON THE GAME WHEEEEEEEEEEEEEEEEEEY"))
		}
	}
	
}

void URadio::PlaceBattery()
{
	BatteryPlaced = true;
}

