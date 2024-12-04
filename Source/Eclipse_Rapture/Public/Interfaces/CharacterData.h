// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CharacterData.generated.h"

UINTERFACE(MinimalAPI)
class UCharacterData : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ECLIPSE_RAPTURE_API ICharacterData
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Inverse Kinematics")
	FTransform GetLHIK() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Inverse Kinematics")
	void GetHandSwayData(float& SideMove, float& MouseX, float& MouseY) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Character")
	USkeletalMeshComponent* GetSkeleton() const;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapons")
	bool I_HasWeaponEquipped() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapons")
	bool I_GetIsAiming();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapons")
	bool I_GetIsReloading();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Weapons")
	FHitResult I_GetCurrentWeaponTraceInfo();


};
