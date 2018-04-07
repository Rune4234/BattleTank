// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories= ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downward speed, and +1 is max upwards speed.
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	// Maximum number of degrees per second the barrel is allowed to move.
	float MaxDegreesPerSecond = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	// Maximum elevation in degrees the barrel is allowed to move.
	float MaxElevation = 35.0f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	// Minimum elevation in degrees the barrel is allowed to move.
	float MinElevation = 0.0f;
};
