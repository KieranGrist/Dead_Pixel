// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include"Radio.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DoorKey.h"
#include "Door.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GrabObject.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEADPIXEL_API UGrabObject : public UActorComponent
{
	GENERATED_BODY()

public:	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Sets default values for this component's properties
	UGrabObject();

	// Called when the game starts

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	void OpenDoor();

	void ActivateRadio();

	void PlaceBattery();



	void PickupItem();

	void UnlockDoor();


	// Ray-cast and grab what's in reach
	void Grab();

	// Called when grab is released
	void Release();

	// Find (assumed) attached phyics handle
	void FindPhysicsHandleComponent();

	// Setup (assumed) attached input component
	void SetupInputComponent();

	// Return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();

	// Returns current start of reach line
	FVector GetReachLineStart();

	// Returns current end of reach line
	FVector GetReachLineEnd();
	UPROPERTY(EditAnywhere)
		AActor* Radio;
private:
	// How far ahead of the player can we reach in cm
	

		URadio* RadioComponent;
	UPROPERTY(VisibleAnywhere)
	float Reach = 500.f;
	UPROPERTY(VisibleAnywhere)
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UPROPERTY(VisibleAnywhere)
	UInputComponent* InputComponent = nullptr;
	UPROPERTY(VisibleAnywhere)
	bool Key;
	UPROPERTY(VisibleAnywhere)
	UDoorKey* KeyDetails = nullptr;
	UPROPERTY(VisibleAnywhere)
	bool BatteryInInventory = false;
};
