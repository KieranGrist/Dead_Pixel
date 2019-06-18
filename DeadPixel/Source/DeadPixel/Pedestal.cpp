// Fill out your copyright notice in the Description page of Project Settings.

#include "Pedestal.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UPedestal::UPedestal()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


}


// Called when the game starts
void UPedestal::BeginPlay()
{
	Super::BeginPlay();

	FString ObjectName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("Pedestal Reporting for duty On : %s"), *ObjectName);
	//Find the owning actor
	if (GetOwner()->FindComponentByClass < UDoor>()) {
	Door = GetOwner()->FindComponentByClass < UDoor>();
}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Pedestal Puzzle is not on a door or is missing the door component : %s"), *ObjectName);
	}

}


// Called every frame
void UPedestal::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//	GoldTotum = GetWorld()->GetFirstPlayerController()->GetPawn();




	if (GoldPressurePlate && GoldPressurePlate->IsOverlappingActor(GoldTotum))
	{
		GoldTotum->SetActorLocation(GoldPressurePlate->GetActorLocation() );
		GoldTotum->DisableComponentsSimulatePhysics();
	}

	if (MetalPressurePlate && MetalPressurePlate->IsOverlappingActor(MetalTotum))
	{
		MetalTotum->SetActorLocation(MetalPressurePlate->GetActorLocation());
		MetalTotum->DisableComponentsSimulatePhysics();
	}

	if (RockPressurePlate && RockPressurePlate->IsOverlappingActor(RockTotum))
	{
		RockTotum->SetActorLocation(RockPressurePlate->GetActorLocation() );
		RockTotum->DisableComponentsSimulatePhysics();
	}

	if (GoldPressurePlate && GoldPressurePlate->IsOverlappingActor(GoldTotum) &&
		MetalPressurePlate && MetalPressurePlate->IsOverlappingActor(MetalTotum) &&
		RockPressurePlate && RockPressurePlate->IsOverlappingActor(RockTotum))
	{
		Door->UnlockDoor();
		Door->OpenDoor();
		Activated = true;
	}
	
}

bool UPedestal::AntenasPlaced() const
{
	return Activated;
}

