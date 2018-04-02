// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	

}


void UTankAimingComponent::AimAt(FVector WorldSpaceAim)
{
	FString OurTankName = GetOwner()->GetName();
	if (!Barrel) {
		UE_LOG(LogTemp, Error, TEXT("%s has not set barrel reference."), *(OurTankName))
		return;
	} else {
		FVector BarrelLocation = Barrel->GetComponentLocation();
		UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *(OurTankName), *(WorldSpaceAim.ToString()), *(BarrelLocation.ToString()))
	}
}


void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}