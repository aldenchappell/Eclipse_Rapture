// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/HealthItem.h"
#include "Global/Components/HealthComponent.h"
#include "Character/InventoryComponent.h"

AHealthItem::AHealthItem()
{

}

void AHealthItem::Interact_Implementation(AEclipseRaptureCharacter* Character)
{
	Super::Interact_Implementation(Character);
}

void AHealthItem::Use(AEclipseRaptureCharacter* Character)
{
	if (Character && Character->GetHealthComponent())
	{
		//only remove item from inventory if player is below max health
		if (Character->GetHealthComponent()->GetCurrentHealth()
			< Character->GetHealthComponent()->MaxHealth)
		{
			if (OwningInventory)
			{
				OwningInventory->RemoveItem(GetClass());
			}
			Character->GetHealthComponent()->HealHealth(HealingAmount);
		}
	}
}