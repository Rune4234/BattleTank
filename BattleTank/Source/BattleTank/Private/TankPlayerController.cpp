// Fill out your copyright notice in the Description page of Project Settings.
#include "TankPlayerController.h"	// Must be first include.
#include "BattleTank.h"
#include "Engine/World.h"
#include "Camera/PlayerCameraManager.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

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
			GetControlledTank()->AimAt(HitLocation);
			//TODO tell controlled tank to aim at this point.
		}
	}
}


bool ATankPlayerController::GetSightRayHitLocation(OUT FVector& HitLocation) const
{
	// find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(OUT ViewportSizeX, OUT ViewportSizeY);

	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	
	FVector LookDirection;
	if (!GetLookDirection(ScreenLocation, LookDirection)) {
		UE_LOG(LogTemp, Error, TEXT("Failed to get look direction."))
		return false;
	} else {
		GetLookVectorHitLocation(LookDirection, OUT HitLocation);
		return true;
	}
}


bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, OUT FVector& LookDirection) const
{
	FVector CameraWorldLocation; // This information is not needed for our function.
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		OUT CameraWorldLocation, 
		OUT LookDirection
	);
}


bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, OUT FVector& HitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	bool bLineTraceSuccess = GetWorld()->LineTraceSingleByChannel(
		OUT HitResult,
		StartLocation,
		StartLocation + (LookDirection * LineTraceRange),
		ECollisionChannel::ECC_Visibility
	);
	if (!bLineTraceSuccess) { 
		OUT HitLocation = FVector(0.0f);
		return false;
	} else {
		OUT HitLocation = HitResult.Location;
		return true;
	}
}