// CopyRight@EagerBeaver

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::IntendMoveForward(float Throw) {
	UE_LOG(LogTemp, Warning, TEXT("%s Intend move forward throw %f"), *GetOwner()->GetName(), Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::Initilize(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) {
		return;
	}
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}
