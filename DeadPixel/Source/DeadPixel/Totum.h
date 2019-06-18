// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Totum.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEADPIXEL_API UTotum : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTotum();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void GetTotum() const;
private:
	UPROPERTY(EditAnywhere)
		int TotumID = 5;
		
	
};
