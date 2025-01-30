#pragma once

#include "Weapons/WeaponTypes.h"
#include "CoreMinimal.h"
#include "WeaponData.generated.h"

USTRUCT(BlueprintType)
struct FWeaponData : public FTableRowBase
{
	GENERATED_BODY()

#pragma region Weapon Data
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	TSubclassOf<class AWeaponBase> WeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	TSubclassOf<class AWeaponPickup> PickupClass;

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	TArray<EWeaponFireMode> FireModes;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	float Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	float BaseDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	float BodyDamageMultiplier = 1.15f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	float CriticalDamageMultiplier = 1.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	float ReloadTime;

#pragma endregion

#pragma region Ammo

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	EAmmoType AmmoType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	TSubclassOf<class AAmmoItem> RequiredAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	int32 MaxMagazineSize;

#pragma endregion

#pragma region Recoil

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Weapon Data | Recoil")
	float RecoilMultiplier = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Weapon Data | Recoil")
	float SideRecoilMultiplier = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Weapon Data | Recoil")
	float KickbackRecoilMultiplier = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Weapon Data | Recoil")
	float KicksideRecoilMultiplier = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Weapon Data | Recoil")
	float KickupRecoilMultiplier = 1.f;

#pragma endregion

#pragma region FX

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | FX")
	TObjectPtr<UParticleSystem> MuzzleFlashFX;

#pragma endregion

#pragma region Sounds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data | Sound")
	TObjectPtr<USoundBase> HitSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	TObjectPtr<USoundBase> OutOfAmmoSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	TObjectPtr<USoundBase> ShootSound;
#pragma endregion

#pragma region Animation
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Weapon Data | Animation")
	TObjectPtr<UAnimMontage> FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Weapon Data | Animation")
	TObjectPtr<UAnimMontage> ReloadMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Weapon Data | Animation")
	TObjectPtr<UAnimMontage> EquipMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Weapon Data | Animation")
	TObjectPtr<UAnimMontage> UnequipMontage;



#pragma endregion

#pragma region Types
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	EWeaponType WeaponSlotType = EWeaponType::EWT_Unarmed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	EWeaponClass WeaponClassType = EWeaponClass::EWC_Unarmed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	EWeaponName WeaponNameType = EWeaponName::EWN_Unarmed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	FName SocketName;

#pragma endregion

#pragma region Visuals

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data | Visuals")
	float ClippingFOV = 80.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data | Visuals")
	float ClippingRenderDepth = 0.2f;


#pragma endregion
};