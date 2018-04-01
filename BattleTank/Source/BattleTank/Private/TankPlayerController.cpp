// Fill out your copyright notice in the Description page of Project Settings.
#include "TankPlayerController.h"	// Must be first include.
#include "BattleTank.h"

#define OUT

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Error, TEXT("PlayerController not posessing a tank."))
	} else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController posessing: %s"), *(ControlledTank->GetName()))
	}
}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
	else {
		FVector HitLocation;
		if (GetSightRayHitLocation(OUT HitLocation))
		{
			UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *HitLocation.ToString());

			// get world location of linetrace through crosshair
			// if it hits the landsacpe
				// tell controlled tank to aim at this point
		}
	}
}


bool ATankPlayerController::GetSightRayHitLocation(OUT FVector& HitLocation) const
{
	// find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(OUT ViewportSizeX, OUT ViewportSizeY);

	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	// "de-project" screen position of crosshair to a world direction
	// line-trace along that look direction and see what we hit (up to max range)
	return true;
}