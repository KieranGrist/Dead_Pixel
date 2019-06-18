// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Door.h"
#include "Pedestal.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEADPIXEL_API UPedestal : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPedestal();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	bool AntenasPlaced() const;
private:
	bool Activated;
	//
	UPROPERTY(EditAnywhere)
	ATriggerVolume* GoldPressurePlate;
	UPROPERTY(EditAnywhere)
	ATriggerVolume* MetalPressurePlate;
	UPROPERTY(EditAnywhere)
	ATriggerVolume* RockPressurePlate;
	UPROPERTY(EditAnywhere)
	AActor* GoldTotum;
	UPROPERTY(EditAnywhere)
		AActor* MetalTotum;
	UPROPERTY(EditAnywhere)
		AActor* RockTotum;
	UPROPERTY(EditAnywhere)
	
	
	UDoor* Door; //Door To Open
	
};
