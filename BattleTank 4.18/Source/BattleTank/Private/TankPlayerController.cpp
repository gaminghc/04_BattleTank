// CopyRight@EagerBeaver

#include "TankPlayerController.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("Player Controller not possessing a tank!"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player Controller possessing %s"), *ControlledTank->GetName());
	}
}

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

bool ATankPlayerController::IsTargetingAnotherTank() const
{
	return bIsTargetingAnotherTank;
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	AimTowardCrossHair();

}

void ATankPlayerController::AimTowardCrossHair() {
	if (!GetControlledTank()) return;

	// Get where in the world the cross hair hits and
	// tell the tank to point there
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) {
		//UE_LOG(LogTemp, Warning, TEXT("Hit location: %s"), *HitLocation.ToString());
		GetControlledTank()->AimAt(HitLocation);
	}
}


bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) {
	// Find cross-hair position in pixel coords
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	//UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString());

	// De-project screen position to world
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		//UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *LookDirection.ToString());
		// Line trace to see what we hit
		if (GetLookVectorHitLocation(LookDirection, OutHitLocation)) {
			//UE_LOG(LogTemp, Warning, TEXT("Crosshair hits: %s"), *OutHitLocation.ToString());
		}
		else {
			return false;
		}
	}
	
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &OutWorldDirection)
{
	FVector OutWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, OutWorldLocation, OutWorldDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector & HitLocation)
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LookDirection * LineTraceRange;
	bIsTargetingAnotherTank = false;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		if (HitResult.Actor->GetClass()->IsChildOf(ATank::StaticClass())) {
			bIsTargetingAnotherTank = true;
		}
		return true;
	}
	
	HitLocation = FVector(0);
	return false; // line trace didn't hit
}
