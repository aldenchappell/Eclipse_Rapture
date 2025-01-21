// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapons/WeaponData.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Refs")
	TObjectPtr<class AEclipseRaptureCharacter> OwningCharacter;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon | Components")
	TObjectPtr<class UWeaponDataComponent> WeaponDataComponent;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon | Weapon Properties")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon | Weapon Properties")
	bool bCanFire = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Weapon Properties")
	int32 WeaponIndex;

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, BlueprintCallable, Category = "Weapon | Weapon Data")
	FDataTableRowHandle GetWeaponID();

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, BlueprintCallable, Category = "Weapon | Weapon Data")
	FWeaponData GetWeaponData();

#pragma region WeaponStats

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Weapon Stats")
	float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Weapon Stats")
	float Range;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Weapon Stats")
	float FireRate = 0.2f;

	
#pragma endregion



#pragma region Sounds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	TObjectPtr<USoundBase> HitSound;
#pragma endregion

#pragma region Animation
	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Weapon | Animation")
	TObjectPtr<UAnimSequence> FireAnimation;
	
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
	FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() const { return WeaponMesh; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE FName GetAttachName() const { return SocketName; }
};
