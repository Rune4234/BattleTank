// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

#define OUT


UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UTankAimingComponent::AimAt(FVector WorldSpaceAim, float LaunchSpeed)
{
	if (!Barrel || !Turret) {
		UE_LOG(LogTemp, Error, TEXT("%s has no reference to Barrel or Turret, check Blueprint to make sure they are referenced."), *(GetOwner()->GetName()))
		return;
	}
	else {
		FVector LaunchVelocity;
		FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
		bool bSuggestProjectileVelocitySuccess = UGameplayStatics::SuggestProjectileVelocity
		(
			this,
			OUT LaunchVelocity,
			StartLocation,
			WorldSpaceAim,
			LaunchSpeed,
			false,
			0.0f,
			0.0f,
			ESuggestProjVelocityTraceOption::DoNotTrace
		);
		if (!bSuggestProjectileVelocitySuccess) { return; }
		else {
			FVector AimDirection = LaunchVelocity.GetSafeNormal();
			MoveBarrelTowards(AimDirection);
		}
	}
}


void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) 
{
	// work out difference between current barrel rotation and aim direction.
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	if (!BarrelToSet) { return; }
	else {
		Barrel = BarrelToSet;
	}
}


void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	if (!TurretToSet) { return; }
	else {
		Turret = TurretToSet;
	}
}