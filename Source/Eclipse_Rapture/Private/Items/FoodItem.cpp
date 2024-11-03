// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/FoodItem.h"
#include "Global/Components/HealthComponent.h"
#include "Character/InventoryComponent.h"


AFoodItem::AFoodItem()
{

}

void AFoodItem::Interact_Implementation(AEclipseRaptureCharacter* Character)
{

}

void AFoodItem::Use(AEclipseRaptureCharacter* Character)
{
	if (Character && Character->GetHealthComponent())
	{
		Character->GetHealthComponent()->HealSatiety(FoodSatietyHealAmount);

		//only remove item from inventory if player is below max satiety
		if (Character->GetHealthComponent()->GetCurrentSatiety()
			< Character->GetHealthComponent()->MaxSatiety)
		{
			if (OwningInventory)
			{
				OwningInventory->RemoveItem(GetClass());
			}
		}
	}
}
