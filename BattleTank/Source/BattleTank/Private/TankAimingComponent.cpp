// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#define OUT

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


void UTankAimingComponent::AimAt(FVector WorldSpaceAim, float LaunchSpeed)
{
	if (!Barrel) {
		UE_LOG(LogTemp, Error, TEXT("%s has no reference to barrel."), *(GetOwner()->GetName()))
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

	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *(DeltaRotator.ToString()))
	// move the barrel the right amount this frame, given max elevation speed and frame time.
}


void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}