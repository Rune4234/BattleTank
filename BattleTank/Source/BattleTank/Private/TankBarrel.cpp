// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
	// move the barrel the right amount this frame, given max elevation speed and frame time.
	float Time = GetWorld()->GetTimeSeconds();
	
}
