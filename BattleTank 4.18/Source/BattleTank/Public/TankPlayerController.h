// CopyRight@EagerBeaver

#pragma once

#include "Engine/World.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Update")
	bool IsTargetingAnotherTank() const;

private: 
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// move barrel and turrent to point to cross hair
	void AimTowardCrossHair();

	// true if hit landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation);

	bool GetLookDirection(FVector2D ScreenLocation, FVector &OutWorldDirection);

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation);

	bool bIsTargetingAnotherTank = false;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairYLocation = 0.3333;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000; // 10km

protected:

	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;

};
