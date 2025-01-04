// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/WeaponPickup.h"
#include "Character/InventoryComponent.h"

AWeaponPickup::AWeaponPickup()
{

}

void AWeaponPickup::Interact_Implementation(AEclipseRaptureCharacter* Character)
{
	if (Character)
	{
		Character->SpawnItem(WeaponToSpawn);
		UInventoryComponent* Inventory = Character->GetInventoryComponent();
		if (Inventory)
		{
			//TODO: Come back to this to add to inventory
			//Character->InventoryComponent->AddItemAmount(GetClass(), 1);
			//Inventory->TryAddItem(this);
			Inventory->OnInventoryUpdated.Broadcast();
		}
		
		Destroy();
	}
}

