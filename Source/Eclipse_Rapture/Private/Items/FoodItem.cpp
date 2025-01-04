// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/FoodItem.h"
#include "Global/Components/HealthComponent.h"
#include "Character/InventoryComponent.h"


AFoodItem::AFoodItem()
{

}

void AFoodItem::Interact_Implementation(AEclipseRaptureCharacter* Character)
{
	Super::Interact_Implementation(Character);
}

void AFoodItem::Use(AEclipseRaptureCharacter* Character)
{
	if (Character && Character->GetHealthComponent())
	{
		//only remove item from inventory if player is below max satiety
		if (Character->GetHealthComponent()->GetCurrentSatiety()
			< Character->GetHealthComponent()->MaxSatiety)
		{
			//TODO: Come back to this to remove from inventory
			//TODO: Come back here and fix for new inventory system.
			/*if (OwningInventory)
			{
				OwningInventory->TryRemoveItem(this);
			}*/
			Character->GetHealthComponent()->HealSatiety(FoodSatietyHealAmount);
		}
	}
}
