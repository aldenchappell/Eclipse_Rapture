// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/WeaponBase.h"
#include "RangedWeaponBase.generated.h"

class AAmmoItem;

UCLASS()
class ECLIPSE_RAPTURE_API ARangedWeaponBase : public AWeaponBase
{
	GENERATED_BODY()
	
public:



	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapon | Ammo")
	bool Reload(UInventoryComponent* PlayerInventory);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon | Weapon Stats")
	int32 CurrentFireModeIndex = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Weapon Stats")
	float BurstDelay = .5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Weapon Stats")
	int32 ShotsPerBurst = 3;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon | Ammo")
	int32 CurrentAmmo;

	//when picking this weapon up, will it spawn with a random amount of ammo, or max ammo?
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Weapon | Ammo")
	bool bEnableRandomStartingMagSize = false;

public:

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int GetCurrentClipAmmo() const { return CurrentAmmo; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetHasAmmo() const { return CurrentAmmo > 0; }
};
