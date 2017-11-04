// CopyRight@EagerBeaver

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI Controller not possessing a tank!"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Controller possessing %s"), *ControlledTank->GetName());
	}

	auto PlayerTank = GetPlayerTank();

	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI Controller could not find player tank!"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Controller found player tank %s"), *PlayerTank->GetName());
	}
}

void ATankAIController::AimTowardPlayer()
{
	auto PlayerTank = GetPlayerTank();

	if (PlayerTank) {

		auto ControlledTank = GetControlledTank();

		// move toward player
		MoveToActor(PlayerTank, AcceptanceRadius);

		if (ControlledTank) {
			ControlledTank->AimAt(PlayerTank->GetActorLocation());
			ControlledTank->Fire();
		}
	}
}

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerTank) {
		return nullptr;
	} 
	return (ATank*)(PlayerTank);
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	AimTowardPlayer();
}



