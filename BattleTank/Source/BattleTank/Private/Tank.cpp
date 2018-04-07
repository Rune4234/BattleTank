// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"


//auto Time = GetWorld()->GetTimeSeconds();
//UE_LOG(LogTemp, Warning, TEXT("%f: Raw %f"), Time, RawNewElevation)

// Sets default values
ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;

	// No need to protect pointers as added at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	bool bIsReloaded = ((FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds);
//	UE_LOG(LogTemp, Error, TEXT("is reloaded %s"), bIsReloaded ? *FString("true"):*FString("false"))

	if (!Barrel) {
		UE_LOG(LogTemp, Error, TEXT("%s has no reference to Barrel to fire projectile, check Blueprint to ensure it's referenced."), *(GetOwner()->GetName()))
	} else if (bIsReloaded) {
		// Spawn projectile at socket location on barrel.
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
		);
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}