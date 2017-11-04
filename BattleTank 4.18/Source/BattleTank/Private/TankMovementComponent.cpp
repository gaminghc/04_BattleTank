// CopyRight@EagerBeaver

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::IntendMoveForward(float Throw) {
	UE_LOG(LogTemp, Warning, TEXT("%s Intend move forward throw %f"), *GetOwner()->GetName(), Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw) {
	UE_LOG(LogTemp, Warning, TEXT("%s Intend move forward throw %f"), *GetOwner()->GetName(), Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::Initilize(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) {
		return;
	}
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto ForwardThrow = FVector::DotProduct(TankForwardDirection, AIForwardIntention);
	IntendMoveForward(ForwardThrow);

	auto RightThrow = FVector::CrossProduct(TankForwardDirection, AIForwardIntention).Z;
	IntendTurnRight(RightThrow);
}
