// Damageable.h

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Damageable.generated.h"

// Interface class declaration
UINTERFACE(MinimalAPI)
class UDamageable : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for any object that can take damage.
 */
class ECLIPSE_RAPTURE_API IDamageable
{
	GENERATED_BODY()

public:
	// Function that can be implemented in any class that inherits from this interface
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
	void TakeDamage(float DamageAmount, FVector HitLocation);
};