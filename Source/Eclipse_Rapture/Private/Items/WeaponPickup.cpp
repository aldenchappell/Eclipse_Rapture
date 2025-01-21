// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/WeaponPickup.h"
#include "Character/InventoryComponent.h"
#include "Items/Components/ItemDataComponent.h"

AWeaponPickup::AWeaponPickup()
{

}

void AWeaponPickup::Interact_Implementation(AEclipseRaptureCharacter* Character)
{
	
	if (Character)
	{
		UInventoryComponent* Inventory = Character->GetInventoryComponent();
		AWeaponBase* CurrentWeapon = Character->GetCurrentWeapon();

		if (CurrentWeapon)
		{
			//if the characters current weapon is equal to this pickup's weapon name, then add it to their inventory.
			//otherwise, spawn it in their hand.
			if (CurrentWeapon->GetWeaponData().WeaponNameType == WeaponName)
			{
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
				Character->EquipUnarmed();
				Character->SpawnWeapon(WeaponToSpawn);
			}
		}
		else
		{
			Character->EquipUnarmed();
			Character->SpawnWeapon(WeaponToSpawn);
		}

		//should not be necessary. This is just for testing purposes.
		Inventory->OnInventoryUpdated.Broadcast();
		Destroy();
	}
}

