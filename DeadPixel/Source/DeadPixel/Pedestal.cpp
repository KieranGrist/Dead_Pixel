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




	if (GoldAntenaPressurePlate && GoldAntenaPressurePlate->IsOverlappingActor(GoldAntena))
	{
		GoldAntena->SetActorLocation(GoldAntenaPressurePlate->GetActorLocation() );
		GoldAntena->DisableComponentsSimulatePhysics();
	}

	if (SilverAntenaPressurePlate && SilverAntenaPressurePlate->IsOverlappingActor(SilverAntena))
	{
		SilverAntena->SetActorLocation(SilverAntenaPressurePlate->GetActorLocation());
		SilverAntena->DisableComponentsSimulatePhysics();
	}

	if (BrozneAntenaPressurePlate && BrozneAntenaPressurePlate->IsOverlappingActor(BronzeAntena))
	{
		BronzeAntena->SetActorLocation(BrozneAntenaPressurePlate->GetActorLocation() );
		BronzeAntena->DisableComponentsSimulatePhysics();
	}

	if (GoldAntenaPressurePlate && GoldAntenaPressurePlate->IsOverlappingActor(GoldAntena) &&
		SilverAntenaPressurePlate && SilverAntenaPressurePlate->IsOverlappingActor(SilverAntena) &&
		BrozneAntenaPressurePlate && BrozneAntenaPressurePlate->IsOverlappingActor(BronzeAntena))
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

