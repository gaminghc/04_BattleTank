// CopyRight@EagerBeaver

#include "TankTrack.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	UE_LOG(LogTemp, Warning, TEXT("%s on hit"), *GetName());
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// Calculate the slippage speed
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	// Work-out the required acceleration this frame to correct
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	// Calculate and apply sideways force F=ma
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration / 2; // divided by 2 because 2 tracks
	//UE_LOG(LogTemp, Warning, TEXT("%s applying correction force of %s"), *GetName(), *CorrectionForce.ToString());
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	//UE_LOG(LogTemp, Warning, TEXT("FUCK Track"));
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	//UE_LOG(LogTemp, Warning, TEXT("%s tank track throttling at %f"), *GetName(), Throttle);
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}



