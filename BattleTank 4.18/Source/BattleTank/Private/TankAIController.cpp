// CopyRight@EagerBeaver

#include "TankAIController.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATankAIController::AimTowardPlayer()
{
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) return;

	// move toward player
	MoveToActor(PlayerTank, AcceptanceRadius);

	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (AimingComponent->GetFiringState() == EFiringState::Locked) {
		AimingComponent->Fire();
	}

}


void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	AimTowardPlayer();
}



