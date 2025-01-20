#pragma once

#include "Weapons/WeaponTypes.h"
#include "CoreMinimal.h"
#include "WeaponData.generated.h"

USTRUCT(BlueprintType)
struct FWeaponData : public FTableRowBase
{
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	TSubclassOf<class AWeaponBase> WeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	TSubclassOf<class AWeaponPickup> PickupClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	EAmmoType AmmoType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	TSubclassOf<class AAmmoItem> RequiredAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	TArray<EWeaponFireMode> FireModes;

	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	float Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	float BaseDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	float ReloadTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	int32 MaxMagazineSize;

#pragma region Sounds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data | Sound")
	TObjectPtr<USoundBase> HitSound;
#pragma endregion

#pragma region Animation
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Weapon Data | Animation")
	TObjectPtr<UAnimSequence> FireAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Weapon | Animation")
	TObjectPtr<UAnimMontage> EquipMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Weapon | Animation")
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
};