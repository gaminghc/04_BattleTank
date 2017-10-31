// CopyRight@EagerBeaver

#include "TankBarrel.h"
#include "Engine/World.h"


void UTankBarrel::Elevate(float RelativeSpeed) {

	//auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("%f: Barrel elevating at speed %f"), Time, DegreesPerSecond);
	auto ElevationChange = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f) * MaxDegreesPerSecond * (GetWorld()->DeltaTimeSeconds);
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	SetRelativeRotation(FRotator(FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees), 0, 0));
}