// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h" // Must be first include.
#include "Tank.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank* ControlledTank = Cast<ATank>(GetPawn());
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (PlayerTank)
	{
		//TODO Move towards the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		
		// Fire if ready.
		ControlledTank->Fire(); // TODO dont fire every frame
	}
	
}
