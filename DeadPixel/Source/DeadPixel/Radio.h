// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include"Pedestal.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Radio.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEADPIXEL_API URadio : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URadio();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void ActivateRadio();
	void PlaceBattery();
private:
	UPROPERTY(EditAnywhere)
		AActor* Battery;
	UPROPERTY(EditAnywhere)
		AActor* AntenaControler;
	UPedestal* Anteneas;
	UPROPERTY(VisibleAnywhere)
	bool BatteryPlaced;
	UPROPERTY(VisibleAnywhere)	
	bool AntenasPlaced;
	
};
