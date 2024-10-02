// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Interfaces/Fire.h"
#include "WeaponTypes.h"
#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "WeaponBase.generated.h"

//Forward Declarations
class UAnimationAsset;
class UAnimMontage;


UCLASS()
class ECLIPSE_RAPTURE_API AWeaponBase : public AActor, public IFire
{
	GENERATED_BODY()
	
public:
	AWeaponBase();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Weapon Properties")
	TSubclassOf<class AWeaponPickup> PickupClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Weapon Properties")
	FName SocketName;

	virtual void Fire_Implementation() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon | Weapon Properties")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon | Ammo")
	bool bCanFire = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Weapon Properties")
	int32 WeaponIndex;
#pragma region WeaponStats
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Weapon Stats")
	float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Weapon Stats")
	float Range;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Weapon Stats")
	float FireRate;
#pragma endregion

#pragma region Ammo
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon | Ammo")
	int32 CurrentAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Ammo")
	int32 MaxAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Ammo")
	int32 ClipSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon | Ammo")
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

#pragma region Animation
	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Weapon | Animation")
	TObjectPtr<UAnimSequence> FireAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Weapon | Animation")
	TObjectPtr<UAnimMontage> AimFireMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Weapon | Animation")
	TObjectPtr<UAnimMontage> HipfireMontage;

#pragma endregion

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EWeaponType WeaponType = EWeaponType::EWT_Unarmed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EWeaponFireMode WeaponFireMode = EWeaponFireMode::EWFM_SemiAuto;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EWeaponClass WeaponClass = EWeaponClass::EWC_Unarmed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EWeaponName WeaponName = EWeaponName::EWN_Unarmed;

	

public: //Getters and Setters
	FORCEINLINE EWeaponType GetWeaponType() const { return WeaponType; }
	FORCEINLINE EWeaponFireMode GetWeaponFireMode() const { return WeaponFireMode; }
	FORCEINLINE EWeaponName GetWeaponName() const { return WeaponName; }
	FORCEINLINE EWeaponClass GetWeaponClass() const { return WeaponClass; }
	FORCEINLINE float GetFireRate() const { return FireRate; }
	FORCEINLINE bool GetCanFire() const { return bCanFire; }
    FORCEINLINE void SetCanFire(bool NewCanFire) { bCanFire = NewCanFire; }
	FORCEINLINE float GetCurrentClipAmmo() const { return CurrentClipAmmo; }
};
