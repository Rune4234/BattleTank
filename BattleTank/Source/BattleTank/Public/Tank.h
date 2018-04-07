// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;	// Forward declaration.
class UTankAimingComponent;
class UTankMovementComponent;
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = Setup)
	// Sets reference to the tanks barrel asset for our C++ class.
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	// Sets reference to the tanks turret asset for our C++ class.
	void SetTurretReference(UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Firing)
	// Method to fire the tank, callable via Blueprint.
	void Fire();

	void AimAt(FVector HitLocation);

protected:
	// Stores reference to the TankAimingComponent.
	UTankAimingComponent* TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	// Stores reference to the TankMovementComponent.
	UTankMovementComponent* TankMovementComponent = nullptr;

private:	
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	// Reference to Blueprint class of Projectile, set in Blueprint editor.
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	// Time in seconds to wait before we can fire the tanks gun again.
	float ReloadTimeInSeconds = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	// Launch speed for projectile.
	float LaunchSpeed = 4000.0f;

	// Local barrel reference for spawning projectile.
	UTankBarrel* Barrel = nullptr;

	// Stores the last time the tanks gun was fired.
	double LastFireTime = 0;


	// Sets default values for this pawn's properties.
	ATank();
};
