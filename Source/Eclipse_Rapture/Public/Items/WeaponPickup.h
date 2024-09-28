// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapons/WeaponBase.h"
#include "CoreMinimal.h"
#include "Items/Item.h"
#include "WeaponPickup.generated.h"

/**
 * 
 */
UCLASS()
class ECLIPSE_RAPTURE_API AWeaponPickup : public AItem
{
	GENERATED_BODY()
	
public:
	AWeaponPickup();
	virtual void Interact_Implementation(AEclipseRaptureCharacter* Character) override;
	

protected:
	//UPROPERTY(BlueprintReadonly, EditAnywhere, Category = "Weapon Properties")
	//TSubclassOf<class WeaponBase> WeaponToSpawn;

private:

};
