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

		if (Character->InventoryComponent)
		{
			//Character->InventoryComponent->AddItemAmount(GetClass(), 1);
			Character->InventoryComponent->OnInventoryUpdated.Broadcast();
		}
		
		Destroy();
	}
}

