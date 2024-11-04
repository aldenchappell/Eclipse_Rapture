// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/WaterItem.h"
#include "Global/Components/HealthComponent.h"
#include "Character/InventoryComponent.h"


AWaterItem::AWaterItem()
{

}

void AWaterItem::Interact_Implementation(AEclipseRaptureCharacter* Character)
{
	Super::Interact_Implementation(Character);
}

void AWaterItem::Use(AEclipseRaptureCharacter* Character)
{
	if (Character && Character->GetHealthComponent())
	{
		//only remove item from inventory if player is below max thirst
		if (Character->GetHealthComponent()->GetCurrentThirst()
			< Character->GetHealthComponent()->MaxThirst)
		{
			if (OwningInventory)
			{
				OwningInventory->RemoveItem(GetClass());
			}
			Character->GetHealthComponent()->HealThirst(ThirstHealAmount);
		}
	}
}
