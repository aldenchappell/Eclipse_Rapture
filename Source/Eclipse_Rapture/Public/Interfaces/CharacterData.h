// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Character/InventoryComponent.h"
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
	FTransform GetRHIK() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Inverse Kinematics")
	void GetHandSwayData(float& SideMove, float& MouseX, float& MouseY) const;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapons")
	bool HasWeaponEquipped() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Inventory")
	class UInventoryComponent* GetInventoryComponent() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Health")
	class UHealthComponent* GetHealthComponent() const;
};
