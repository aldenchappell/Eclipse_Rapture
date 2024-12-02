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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDamageResponse DamageResponse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class AActor> DamageCauser;
};

UINTERFACE(MinimalAPI)
class UDamageable : public UInterface
{
	GENERATED_BODY()
};


class ECLIPSE_RAPTURE_API IDamageable
{
	GENERATED_BODY()

public:
	// Function that can be implemented in any class that inherits from this interface
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
	void TakeDamage(FDamageInfo DamageInfo);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Death Events")
	void DropItems(const TArray<TSubclassOf<class AItem>>& InventoryItems);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Health Messages")
	float GetMaxHealth();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Health Messages")
	float GetCurrentHealth();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Health Messages")
	float GetCriticalHealthThreshold();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Health Messages")
	bool GetIsDead();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Health Tokens")
	void ReserveAttackToken(int32 TokenAmount, bool& Success);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Health Tokens")
	void ReturnAttackToken(int32 TokenAmount);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Teams")
	int32 GetTeamNumber();

	//TODO: Add functions for damage areas (could be bone, could be armor, etc)
};