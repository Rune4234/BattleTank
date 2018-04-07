// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	else {
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(Throw);
	}
	//TODO prevent double-speed due to using fly-by-wire and direct-control.
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	else {
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(Throw * -1);
	}
	//TODO prevent double-speed due to using fly-by-wire and direct-control.
}


