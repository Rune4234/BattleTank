// Fill out your copyright notice in the Description page of Project Settings.
#include "TankPlayerController.h"	// Must be first include.
#include "BattleTank.h"


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

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


