// CopyRight@EagerBeaver

#pragma once

#include "Engine/World.h"
#include "Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

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
	void AimTowardPlayer() const;

	virtual void Tick(float DeltaTime) override;
};
