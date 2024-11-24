// Damageable.h

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Character/DamageTypes.h"
#include "Damageable.generated.h"

USTRUCT(BlueprintType)
struct FDamageInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector HitLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDamageType DamageType;
};

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
	void TakeDamage(FDamageInfo DamageInfo);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Death Events")
	void Die();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Death Events")
	void DropItems(const TArray<TSubclassOf<class AItem>>& InventoryItems);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Health Messages")
	float GetMaxHealth();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Health Messages")
	float GetCurrentHealth();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Health Messages")
	float GetCriticalHealthThreshold();
};