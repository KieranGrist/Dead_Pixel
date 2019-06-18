// Fill out your copyright notice in the Description page of Project Settings.

#include "GrabObject.h"

#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Battery.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Public/DrawDebugHelpers.h"
#define OUT 

// Sets default values for this component's properties
UGrabObject::UGrabObject()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabObject::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandleComponent();
	SetupInputComponent();
	
}


// Called every frame
void UGrabObject::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PhysicsHandle) { return; }
	// if the physics handle is attached
	if (PhysicsHandle->GetGrabbedComponent())
	{
		// move the object that we're holding
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}
	if (Radio->FindComponentByClass<URadio>())
	{
		RadioComponent = Radio->FindComponentByClass<URadio>();
	}
}

void UGrabObject::OpenDoor()
{
	UE_LOG(LogTemp, Error, TEXT("OpenDoor"))
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent(); // gets the mesh in our case
	auto ActorHit = HitResult.GetActor();
	if (ActorHit)
	{
		if (ActorHit->FindComponentByClass<UDoor>())
		{
			ActorHit->FindComponentByClass<UDoor>()->OpenDoor();
		}
	}
}
void UGrabObject::ActivateRadio()
{
	UE_LOG(LogTemp, Error, TEXT("Activate Radio"))
	FHitResult HitResult;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),
		TraceParameters
	);
	AActor* ActorHit = HitResult.GetActor();
	if (ActorHit) {
		if (ActorHit->FindComponentByClass<URadio>())
		{
			RadioComponent->ActivateRadio();
		}
	}
}
void UGrabObject::PlaceBattery()
{
	if (BatteryInInventory) {
		UE_LOG(LogTemp, Error, TEXT("Place Battery"))
			FHitResult HitResult;
		FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
		GetWorld()->LineTraceSingleByObjectType(
			OUT HitResult,
			GetReachLineStart(),
			GetReachLineEnd(),
			FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),
			TraceParameters
		);

		AActor* ActorHit = HitResult.GetActor();
		if (ActorHit) {

			if (ActorHit->FindComponentByClass<URadio>())
			{
				RadioComponent->PlaceBattery();
			}
		}
	}
}
void UGrabObject::PickupItem()
{
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent(); // gets the mesh in our case
	auto ActorHit = HitResult.GetActor();
	if (ActorHit)
	{
		if (ActorHit->FindComponentByClass<UDoorKey>())
		{
			UE_LOG(LogTemp, Error, TEXT("Pickup Key"))
			KeyDetails = ActorHit->FindComponentByClass<UDoorKey>();
			ActorHit->Destroy();
			Key = true;
		}
		if (ActorHit->FindComponentByClass<UBattery>())
		{
			UE_LOG(LogTemp, Error, TEXT("Pickup Battery"))
				ActorHit->Destroy();
				BatteryInInventory = true;

		}
	}
}

void UGrabObject::UnlockDoor()
{
	UE_LOG(LogTemp, Error, TEXT("UnlockDoor"))
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent(); // gets the mesh in our case
	auto ActorHit = HitResult.GetActor();
	if (ActorHit)
	{
		if (ActorHit->FindComponentByClass<UDoor>())
		{
			if (KeyDetails != nullptr)
				ActorHit->FindComponentByClass<UDoor>()->UnlockDoor(KeyDetails);
		}
	}
}

void UGrabObject::Grab()
{
	UE_LOG(LogTemp, Error, TEXT("Grab"))
	/// LINE TRACE and see if we reach any actors with physics body collision channel set
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent(); // gets the mesh in our case
	auto ActorHit = HitResult.GetActor();

	/// If we hit something then attach a physics handle
	if (ActorHit)
	{
		if (!PhysicsHandle) { return; }
		PhysicsHandle->GrabComponent(
			ComponentToGrab,
			NAME_None, // no bones needed
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true // allow rotation
		);
	}
}

void UGrabObject::Release()
{

	if (!PhysicsHandle) { return; }
	PhysicsHandle->ReleaseComponent();
}

void UGrabObject::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *GetOwner()->GetName())
	}
}

void UGrabObject::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("GrabObject", IE_Pressed, this, &UGrabObject::Grab);
		InputComponent->BindAction("GrabObject", IE_Released, this, &UGrabObject::Release);
		InputComponent->BindAction("PickupItem", IE_Pressed, this, &UGrabObject::PickupItem);
		InputComponent->BindAction("UnlockDoor", IE_Pressed, this, &UGrabObject::UnlockDoor);
		InputComponent->BindAction("OpenDoor", IE_Pressed, this, &UGrabObject::OpenDoor);
		InputComponent->BindAction("ActivateRadio", IE_Pressed, this, &UGrabObject::ActivateRadio);
		InputComponent->BindAction("PlaceBattery", IE_Pressed, this, &UGrabObject::PlaceBattery);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName())
	}
}

const FHitResult UGrabObject::GetFirstPhysicsBodyInReach()
{
	/// Line-trace (AKA ray-cast) out to reach distance
	FHitResult HitResult;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	AActor* ActorHit = HitResult.GetActor();
	return HitResult;
}

FVector UGrabObject::GetReachLineStart()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	return PlayerViewPointLocation;
}

FVector UGrabObject::GetReachLineEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}

