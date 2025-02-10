// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/WeaponPickup.h"
#include "Character/InventoryComponent.h"
#include "Items/Components/ItemDataComponent.h"
#include "Character/EclipseRaptureCharacter.h"
#include "Weapons/RangedWeaponBase.h"
#include "Weapons/MeleeWeaponBase.h"
AWeaponPickup::AWeaponPickup()
{

}

void AWeaponPickup::Interact_Implementation(AEclipseRaptureCharacter* Character)
{
	if (Character)
	{
		UInventoryComponent* Inventory = Character->GetInventoryComponentRef();

		// Retrieve the weapon type of the new weapon being picked up
		EWeaponType NewWeaponType = WeaponToSpawn->GetDefaultObject<AWeaponBase>()->GetWeaponData().WeaponSlotType;

		// Retrieve the player's primary, secondary, and melee weapons
		ARangedWeaponBase* PrimaryWeapon = Character->GetPrimaryWeapon();
		ARangedWeaponBase* SecondaryWeapon = Character->GetSecondaryWeapon();
		AMeleeWeaponBase* MeleeWeapon = Character->GetMeleeWeapon();

		// Check if any of these weapons have the same weapon type as the new weapon
		bool bHasMatchingWeaponType =
			(PrimaryWeapon && PrimaryWeapon->GetWeaponData().WeaponSlotType == NewWeaponType) ||
			(SecondaryWeapon && SecondaryWeapon->GetWeaponData().WeaponSlotType == NewWeaponType) ||
			(MeleeWeapon && MeleeWeapon->GetWeaponData().WeaponSlotType == NewWeaponType);

		if (bHasMatchingWeaponType)
		{
			// Add to inventory if the player already has a weapon of the same type
			if (Inventory)
			{
				FDataTableRowHandle DataRow = DataComponent->ItemID;
				FName ItemDataID = DataRow.RowName;
				int32 QuantityLeft = 0;

				Inventory->AddToInventory(ItemDataID, 1, QuantityLeft);
			}
		}
		else
		{
			// If the player does not have a weapon of this type, equip it
			Character->EquipUnarmed(false);
			Character->SpawnWeapon(WeaponToSpawn);
		}

		// Notify UI update
		if (Inventory)
		{
			Inventory->OnInventoryUpdated.Broadcast();
		}

		// Destroy the weapon pickup actor
		Destroy();
	}
}



