// CopyRight@EagerBeaver

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY()
	FOnDeathDelegate OnDeath;

private:
	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const & DamageEvent,
		class AController * EventInstigator,
		AActor * DamageCauser
	) override;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 MaxHealth = 1000;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 CurrentHealth = MaxHealth;

	
};
