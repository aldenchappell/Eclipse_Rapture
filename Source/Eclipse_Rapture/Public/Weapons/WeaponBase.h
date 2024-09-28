// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WeaponTypes.h"
#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "WeaponBase.generated.h"

class AWeaponPickup;
/**
 * 
 */
UCLASS()
class ECLIPSE_RAPTURE_API UWeaponBase : public USkeletalMeshComponent
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon | Weapon Properties")
	TObjectPtr<AWeaponPickup> WeaponPickup;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Weapon Properties")
	FName SocketName;

protected:


#pragma region WeaponStats
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Weapon Stats")
	float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Weapon Stats")
	float Range;
#pragma endregion

#pragma region Ammo
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Ammo")
	int32 CurrentAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Ammo")
	int32 MaxAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Ammo")
	int32 ClipSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Ammo")
	int32 CurrentClipAmmo;
#pragma endregion

#pragma region Sounds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	TObjectPtr<USoundBase> HitSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	TObjectPtr<USoundBase> ShootSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	TObjectPtr<USoundBase> ReloadSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	TObjectPtr<USoundBase> EquipSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	TObjectPtr<USoundBase> UnequipSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	TObjectPtr<USoundBase> BulletImpactSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	TObjectPtr<USoundBase> MuzzleSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	TObjectPtr<USoundBase> ReloadFinishedSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	TObjectPtr<USoundBase> ReloadStartSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	TObjectPtr<USoundBase> OutOfAmmoSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	TObjectPtr<USoundBase> AimSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	TObjectPtr<USoundBase> UnaimSound;
#pragma endregion

private:
	EWeaponType WeaponType = EWeaponType::EWT_Unarmed;
	EWeaponFireMode WeaponFireMode = EWeaponFireMode::EWFM_SemiAuto;
	EWeaponName WeaponName = EWeaponName::EWN_Unarmed;
};
