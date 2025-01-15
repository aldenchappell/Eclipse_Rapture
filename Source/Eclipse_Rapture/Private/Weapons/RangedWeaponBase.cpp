// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/RangedWeaponBase.h"

void ARangedWeaponBase::Reload(UInventoryComponent* PlayerInventory)
{
	//   if (!PlayerInventory || !RequiredAmmo) return;

	//   //TODO: Come back here and fix for new inventory system.
	//   // Get the current amount of ammo available in the player's inventory
	//   //int32 InventoryAmmo = PlayerInventory->GetItemAmount(RequiredAmmo);
	   //
	//   // Calculate the remaining space in the magazine
	//   int32 AmmoNeeded = MaxMagazineSize - CurrentAmmo;
	   ////Get the ID of the ammo item
	//   FDataTableRowHandle AmmoRow = RequiredAmmo->GetDefaultObject<AItem>()->DataComponent->ItemID;
	   //FName ItemID = AmmoRow.RowName;
	//   int32 InventoryAmmo = 0;

	   //const UDataTable* ItemTable = RequiredAmmo->GetDefaultObject<AItem>()->DataComponent->ItemID.DataTable;
	//   if (ItemTable->FindRow<FItemData>(ItemID, TEXT(""), true))
	//   {
	//       for (const FInventorySlotData& Slot : PlayerInventory->InventoryItems)
	//       {
	//           if (Slot.ItemID == ItemID)
	//           {
	//               InventoryAmmo = Slot.Quantity;
	//               break;
	//           }
	//       }


	//       //TODO: Come back here and fix for new inventory system.
	//       // Determine the actual amount of ammo to load (minimum of needed ammo and available inventory ammo)
	//       int32 AmmoToLoad = FMath::Min(AmmoNeeded, InventoryAmmo);

	//       // If there is ammo to load, add it to the current magazine and update the inventory
	//       if (AmmoToLoad > 0)
	//       {
	//           CurrentAmmo += AmmoToLoad;

	//           //    //TODO: Come back here and fix for new inventory system.
	//               // Remove the used ammo from the player's inventory

	//          // PlayerInventory->RemoveFromInventory(ItemID, AmmoToLoad, CurrentAmmo);
	//       }

	//       // Ensure the weapon is ready to fire if there's any ammo in the magazine
	//       SetCanFire(true);
	//   }
	//   else
	//   {
	   //	UE_LOG(LogTemp, Warning, TEXT("WeaponBase.cpp/Reload: Ammo item not found in data table."));
	//   }


}
