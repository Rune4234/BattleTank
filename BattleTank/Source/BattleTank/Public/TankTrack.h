// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"


UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Input)
		// Sets a throttle between -1 and +1.
	void SetThrottle(float Throttle);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	// Maximum force per track in Newtons.
	float TrackMaxDrivingForce = 400000.0f; //TODO figure out sensible value, this one assumes 40 tonne tank and 1g accelleration.
	
};
