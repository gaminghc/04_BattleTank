// CopyRight@EagerBeaver


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/World.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = FPlatformTime::Seconds();
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (FPlatformTime::Seconds() - LastFireTime >  ReloadTimeInSeconds) {
		if (IsBarrelMoving()) {
			FiringState = EFiringState::Aiming;
		}
		else {
			FiringState = EFiringState::Locked;
		}
	}
	BarrelDirectionLastFrame = Barrel->GetForwardVector();
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) return;

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	//UE_LOG(LogTemp, Warning, TEXT("%s Starting location: %s"), *GetOwner()->GetName(), *StartLocation.ToString());
	// Calculate the OutLaunchVelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.f, 
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bHaveAimSolution) {
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto ThisTankName = GetOwner()->GetName();
		//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s with angle %s"), *ThisTankName, *HitLocation.ToString(), *StartLocation.ToString(), *AimDirection.ToString());
		MoveBarrelToward(AimDirection);
	}
	else {
		//UE_LOG(LogTemp, Warning, TEXT("No aim solution"));
	}

	
}

void UTankAimingComponent::Initilize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelToward(FVector AimDirection)
{
	// Work out the difference between current barrel rotation, and AimDirection
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;

	//UE_LOG(LogTemp, Warning, TEXT("Aim direction %s as rotator %s"), *AimDirection.ToString(), *AimAsRotator.ToString());

	// Move the barrel and turret right amount given a max elevation speed and the frame time
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) return false;
	if (Barrel->GetForwardVector().Equals(BarrelDirectionLastFrame, 0.01f)) {
		return false;
	}
	return true;
}

void UTankAimingComponent::Fire()
{
	if (FiringState != EFiringState::Reloading) {
		if (ensure(Barrel && ProjectileBlueprint)) {
			// Spawn a projectile at socket of the barrel
			auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")),
				Barrel->GetSocketRotation(FName("Projectile")));
			Projectile->LaunchProjectile(LaunchSpeed);
			LastFireTime = FPlatformTime::Seconds();
			FiringState = EFiringState::Reloading;
		}
	}
}