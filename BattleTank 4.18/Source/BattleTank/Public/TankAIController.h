// CopyRight@EagerBeaver

#pragma once

#include "Engine/World.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	ATank* GetControlledTank() const;

	ATank* GetPlayerTank() const;

	virtual void BeginPlay() override;
	
	// move barrel and turrent to point to cross hair
	void AimTowardPlayer();

	virtual void Tick(float DeltaTime) override;

	// How close the AI tank get to the player
	float AcceptanceRadius = 3000.f;
};
