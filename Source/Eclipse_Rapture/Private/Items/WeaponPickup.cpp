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
		UInventoryComponent* Inventory = Character->GetInventoryComponentRef();
		AWeaponBase* CurrentWeapon = Character->GetCurrentWeapon();

		if (CurrentWeapon)
		{
			// Compare weapon types instead of weapon names
			if (CurrentWeapon->GetWeaponData().WeaponSlotType == WeaponToSpawn->GetDefaultObject<AWeaponBase>()->GetWeaponData().WeaponSlotType)
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

		// Notify UI update
		if (Inventory)
		{
			Inventory->OnInventoryUpdated.Broadcast();
		}

		Destroy();
	}
}


