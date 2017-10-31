// CopyRight@EagerBeaver

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Rotate(float RelativeSpeed) {
	auto RotationChange = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f) * MaxDegreesPerSecond * (GetWorld()->DeltaTimeSeconds);
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0.f, RawNewRotation, 0.f));
}


