// Fill out your copyright notice in the Description page of Project Settings.
#include "TankPlayerController.h"	// Must be first include.
#include "BattleTank.h"
#include "GameFramework/Controller.h"

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


