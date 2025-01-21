// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/RangedWeaponBase.h"
#include "Items/AmmoItem.h"
#include "Character/InventoryComponent.h"
#include "Items/Components/ItemDataComponent.h"
#include "Items/Item.h"


bool ARangedWeaponBase::Reload_Implementation(UInventoryComponent* PlayerInventory)
{
	return false;
	//if (!PlayerInventory || !RequiredAmmo) return;

	////TODO: Come back here and fix for new inventory system.
	//// Get the current amount of ammo available in the player's inventory
	//   
	//// Calculate the remaining space in the magazine
	//int32 AmmoNeeded = MaxMagazineSize - CurrentAmmo;
	////Get the ID of the ammo item
	//FDataTableRowHandle AmmoRow = RequiredAmmo->GetDefaultObject<AAmmoItem>()->DataComponent->ItemID;
	//FName ItemID = AmmoRow.RowName;
	//int32 InventoryAmmo = 0;

	//FInventorySlotData AmmoSlot;

	//const UDataTable* ItemTable = RequiredAmmo->GetDefaultObject<AAmmoItem>()->DataComponent->ItemID.DataTable;
	//if (ItemTable->FindRow<FItemData>(ItemID, TEXT(""), true))
	//{
	//    for (const FInventorySlotData& Slot : PlayerInventory->InventoryItems)
	//    {
	//        if (Slot.ItemID == ItemID)
	//        {
	//            InventoryAmmo = Slot.Quantity;
	//			AmmoSlot = Slot;
	//            break;
	//        }
	//    }


	//    //TODO: Come back here and fix for new inventory system.
	//    // Determine the actual amount of ammo to load (minimum of needed ammo and available inventory ammo)
	//    int32 AmmoToLoad = FMath::Min(AmmoNeeded, InventoryAmmo);

	//    // If there is ammo to load, add it to the current magazine and update the inventory
	//    if (AmmoToLoad > 0)
	//    {
	//        CurrentAmmo += AmmoToLoad;

	//		//TODO: Come back here and fix for new inventory system.
	//		//Remove the used ammo from the player's inventory

	//		int32 FoundQuantity = -1;
	//		int32 FoundIndex = -1;

	//		bool FoundAmmo = PlayerInventory->QueryInventory(AmmoSlot.ItemID, AmmoToLoad, FoundQuantity, FoundIndex);

	//		if (FoundAmmo && FoundIndex > -1)
	//		{
	//			PlayerInventory->RemoveFromInventory(FoundIndex, false, true);
	//		}

	//           
	//    }

	//    // Ensure the weapon is ready to fire if there's any ammo in the magazine
	//    SetCanFire(true);

	//	return true;
	//}
	//else
	//{
	//   	UE_LOG(LogTemp, Warning, TEXT("WeaponBase.cpp/Reload: Ammo item not found in data table."));
	//	return false;
	//}

	//return false;
}

