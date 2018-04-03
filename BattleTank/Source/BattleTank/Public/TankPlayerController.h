// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"	// Must be last include.

#define OUT

class ATank;

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
	UPROPERTY(EditAnywhere)
	// Proportional location of crosshair reticule in the X direction (50%, 33%, etc)
	float CrosshairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	// Proportional location of crosshair reticule in the Y direction (50%, 33%, etc)
	float CrosshairYLocation = 0.33f;

	UPROPERTY(EditAnywhere)
	// Maximum distance in CM to line-trace.
	float LineTraceRange = 1000000.0f;

	ATank* GetControlledTank() const;

	// Get world location of line-trace through crosshair, returns true if hits landscape.
	bool GetSightRayHitLocation(OUT FVector& HitLocation) const;

	// "De-project" screen position of crosshair to a world direction.
	bool GetLookDirection(FVector2D ScreenLocation, OUT FVector& LookDirection) const;

	// Line-trace along the look direction, returns true if something was hit and outputs to HitLocation.
	bool GetLookVectorHitLocation(FVector LookDirection, OUT FVector& HitLocation) const;

	// Start the tank moving the barrel so that a show will hit where the crosshair intersects the world.
	void AimTowardsCrosshair();

};
