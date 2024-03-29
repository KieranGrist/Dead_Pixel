// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DoorKey.h"
#include "Door.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEADPIXEL_API UDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	bool IsLocked() const;
	void OpenDoor();
	void CloseDoor();
	void UnlockDoor();
	void UnlockDoor(UDoorKey *Key);
		
private:
	UPROPERTY(EditAnywhere)
	bool LockStatus = true;
	UPROPERTY(EditAnywhere)
	int KeyIdToUnlock = 5;
};
