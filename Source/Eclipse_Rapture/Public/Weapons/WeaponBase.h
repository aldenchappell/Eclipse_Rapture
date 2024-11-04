// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WeaponTypes.h"
#include "Interfaces/Fire.h"
#include "WeaponTypes.h"
#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "WeaponBase.generated.h"


//Forward Declarations
class UAnimationAsset;
class UAnimMontage;
class UBoxComponent;
class UParticleSystem;
class UAmmoBase;
class AItem;

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

	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> IgnoreActors;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Weapon | Animation")
	TObjectPtr<UAnimMontage> EquipMontage;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnEquip();

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Weapon | Weapon Properties")
	EAmmoType AmmoType;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Weapon | Weapon Properties")
	TSubclassOf<AItem> RequiredAmmo;

#pragma region Recoil Properties(to be used in BP_PlayerMain)

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
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon | Weapon Properties")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon | Ammo")
	bool bCanFire = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Weapon Properties")
	int32 WeaponIndex;

#pragma region Melee

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Melee")
	TObjectPtr<UBoxComponent> MeleeBoxTraceStart;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Melee")
	TObjectPtr<UBoxComponent> MeleeBoxTraceEnd;

	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
					  bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly)
	bool bShouldDoBoxOverlapCheck = false;
#pragma endregion

#pragma region WeaponStats
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Weapon Stats")
	float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Weapon Stats")
	float Range;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Weapon Stats")
	float FireRate = 0.2f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Weapon Stats")
	float BurstDelay = .5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Weapon Stats")
	int32 ShotsPerBurst = 3;
#pragma endregion

#pragma region Ammo
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon | Ammo")
	int32 CurrentAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Ammo")
	int32 MaxHoldableAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Ammo")
	int32 MaxMagazineSize;

	/*UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon | Ammo")
	int32 CurrentClipAmmo;*/
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EWeaponType WeaponType = EWeaponType::EWT_Unarmed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EWeaponFireMode WeaponFireMode = EWeaponFireMode::EWFM_SemiAuto;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EWeaponClass WeaponClass = EWeaponClass::EWC_Unarmed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EWeaponName WeaponName = EWeaponName::EWN_Unarmed;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	TObjectPtr<UBoxComponent> WeaponBox;

public: //Getters and Setters
	UFUNCTION(BlueprintCallable)
	FORCEINLINE EWeaponType GetWeaponType() const { return WeaponType; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE EWeaponFireMode GetWeaponFireMode() const { return WeaponFireMode; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE EWeaponName GetWeaponName() const { return WeaponName; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE EWeaponClass GetWeaponClass() const { return WeaponClass; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetFireRate() const { return FireRate; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetCanFire() const { return bCanFire; }

	UFUNCTION(BlueprintCallable)
    FORCEINLINE void SetCanFire(bool NewCanFire) { bCanFire = NewCanFire; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int GetCurrentClipAmmo() const { return CurrentAmmo; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() const { return WeaponMesh; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UBoxComponent* GetWeaponBox() const { return WeaponBox; }

	UPROPERTY()
	TSubclassOf<AWeaponBase> MeleeWeaponClass{ this->GetClass() };

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetHasAmmo() const { return CurrentAmmo > 0; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetMaxAmmoOnWeapon() { CurrentAmmo = MaxHoldableAmmo; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE int GetMaxMagazineSize() { return MaxMagazineSize; }
};
