// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/WeaponBase.h"
#include "RangedWeaponBase.generated.h"

/**
 * 
 */
UCLASS()
class ECLIPSE_RAPTURE_API ARangedWeaponBase : public AWeaponBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Weapon | Weapon Properties")
	EAmmoType AmmoType;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Weapon | Weapon Properties")
	TSubclassOf<class AAmmoItem> RequiredAmmo;

#pragma region Recoil Properties

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Weapon | Recoil")
	float RecoilMultiplier = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Weapon | Recoil")
	float SideRecoilMultiplier = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Weapon | Recoil")
	float KickbackRecoilMultiplier = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Weapon | Recoil")
	float KicksideRecoilMultiplier = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Weapon | Recoil")
	float KickupRecoilMultiplier = 1.f;

#pragma endregion

#pragma region Reloading

	UFUNCTION(BlueprintCallable, Category = "Weapon | Ammo")
	void Reload(UInventoryComponent* PlayerInventory);

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Weapon | Ammo")
	float ReloadTime = 2.f;

#pragma endregion
protected:

#pragma region Shooting Properties
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Weapon Stats")
	float BurstDelay = .5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Weapon Stats")
	int32 ShotsPerBurst = 3;

#pragma endregion

#pragma region Ammo

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon | Ammo")
	int32 CurrentAmmo;

	//when picking this weapon up, will it spawn with a random amount of ammo, or max ammo?
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Weapon | Ammo")
	bool bEnableRandomStartingMagSize = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Ammo")
	int32 MaxMagazineSize;

#pragma endregion

#pragma region Sounds
	//most of these will be implemented in the actual animations, but mostly here for reference later when we need to implement them.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	TObjectPtr<USoundBase> ShootSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	TObjectPtr<USoundBase> ReloadSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	TObjectPtr<USoundBase> BulletImpactSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	TObjectPtr<USoundBase> OutOfAmmoSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	TObjectPtr<USoundBase> AimSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	TObjectPtr<USoundBase> UnaimSound;
#pragma endregion

#pragma region Animation

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Weapon | Animation")
	TObjectPtr<UAnimMontage> AimFireMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Weapon | Animation")
	TObjectPtr<UAnimMontage> HipfireMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Weapon | Animation")
	TObjectPtr<UAnimMontage> ReloadMontage;


#pragma endregion

#pragma region FX

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | FX")
	TObjectPtr<UParticleSystem> MuzzleFlashFX;

#pragma endregion

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon | Aiming")
	FVector WeaponADSOffset;
private:

public:

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int GetCurrentClipAmmo() const { return CurrentAmmo; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetHasAmmo() const { return CurrentAmmo > 0; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int GetMaxMagazineSize() { return MaxMagazineSize; }
};
