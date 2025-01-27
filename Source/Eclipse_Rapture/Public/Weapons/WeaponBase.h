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


	virtual void Fire_Implementation() override;

	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> IgnoreActors;

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

private:


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EWeaponClass WeaponClass = EWeaponClass::EWC_Unarmed;


public: //Getters and Setters

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, BlueprintCallable, Category = "Weapon | Weapon Data")
	FORCEINLINE FDataTableRowHandle GetWeaponID();

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, BlueprintCallable, Category = "Weapon | Weapon Data")
	FORCEINLINE FWeaponData GetWeaponData();

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, BlueprintCallable, Category = "Weapon | Weapon Data")
	FORCEINLINE FItemData GetPickupItemData();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE EWeaponClass GetWeaponClass() const { return WeaponClass; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool GetCanFire() const { return bCanFire; }

	UFUNCTION(BlueprintCallable)
    FORCEINLINE void SetCanFire(bool NewCanFire) { bCanFire = NewCanFire; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() const { return WeaponMesh; }
};
