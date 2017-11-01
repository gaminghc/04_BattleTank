// CopyRight@EagerBeaver

#include "Tank.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"

class AProjectile;

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation) const
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::SetBarrelReferrence(UTankBarrel * BarrelToSet)
{
	TankAimingComponent->SetBarrelReferrence(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReferrence(UTankTurret * TurretToSet)
{
	TankAimingComponent->SetTurretReferrence(TurretToSet);
}

void ATank::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("%s is firing!"), *GetName());

	if (!Barrel) {
		return;
	}
	else {
		// Spawn a projectile at socket of the barrel
		GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));
	}
}

