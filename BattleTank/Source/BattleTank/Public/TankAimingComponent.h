// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward declaration.
class UTankBarrel;
class UTankTurret;

UENUM()
enum class EFiringStatus : uint8
{
	Locked,
	Aiming,
	Reloading
};

// Holds tank barrel's properties.
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTankAimingComponent();

	void AimAt(FVector WorldSpaceAim, float LaunchSpeed);
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	void SetTurretReference(UTankTurret* TurretToSet);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	// Tank firing status.
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

private:	
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);
};
