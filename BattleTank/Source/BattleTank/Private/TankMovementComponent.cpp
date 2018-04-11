// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"
#include "GameFramework/NavMovementComponent.h"

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

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No call to Super since we're replacing the parents functionality.

	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();

	// Calculate how much forward/backward movement is required.
	float ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);

	float RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendTurnRight(RightThrow);

	UE_LOG(LogTemp, Warning, TEXT("%s right throw %f, forward throw %f"), *GetOwner()->GetName(), RightThrow, ForwardThrow)
}

