// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/WeaponBase.h"
#include "MeleeWeaponBase.generated.h"

/**
 * 
 */
UCLASS()
class ECLIPSE_RAPTURE_API AMeleeWeaponBase : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	AMeleeWeaponBase(); 
protected:
#pragma region Melee

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Melee")
	TObjectPtr<UBoxComponent> MeleeBoxTraceStart;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Melee")
	TObjectPtr<UBoxComponent> MeleeBoxTraceEnd;

	UPROPERTY(EditDefaultsOnly)
	bool bShouldDoBoxOverlapCheck = false;
#pragma endregion
private:

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Weapon Properties", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> WeaponBox;
	

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UBoxComponent* GetWeaponBox() const { return WeaponBox; }
};
