// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Engine/World.h"
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
	PrimaryComponentTick.bCanEverTick = true; //TODO should this tick?!?!?!?
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
		float Time = GetWorld()->GetTimeSeconds();
		if (!bSuggestProjectileVelocitySuccess) {
			
			UE_LOG(LogTemp, Error, TEXT("%f no projectile velocity suggested."), Time); return; }
		else {
			UE_LOG(LogTemp, Warning, TEXT("%f solution gound m8."), Time);
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

	Barrel->Elevate(5); //TODO remove magic number.
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}