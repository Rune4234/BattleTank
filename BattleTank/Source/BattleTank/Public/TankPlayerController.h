// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "TankPlayerController.generated.h"	// Must be last include.

#define OUT

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	// Proportional location of crosshair reticule in the X direction (50%, 33%, etc)
	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5f;

	// Proportional location of crosshair reticule in the Y direction (50%, 33%, etc)
	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.33f;


	ATank* GetControlledTank() const;

	// Start the tank moving the barrel so that a show will hit where the crosshair intersects the world.
	void AimTowardsCrosshair();

	// Get world location of line-trace through crosshair, returns true if hits landscape.
	bool GetSightRayHitLocation(OUT FVector& HitLocation) const;
};
