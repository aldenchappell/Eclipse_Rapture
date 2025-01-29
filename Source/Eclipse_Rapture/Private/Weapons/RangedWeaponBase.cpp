// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/RangedWeaponBase.h"
#include "Items/AmmoItem.h"
#include "Character/InventoryComponent.h"
#include "Items/Components/ItemDataComponent.h"
#include "Items/Item.h"


bool ARangedWeaponBase::Reload_Implementation(UInventoryComponent* PlayerInventory)
{
	return false;
}

