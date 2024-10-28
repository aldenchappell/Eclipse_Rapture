// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/InventoryComponent.h"
#include "Items/Item.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	Capacity = 20;

}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	for (auto& Item : DefaultItems)
	{
		AddItem(Item);
		OnInventoryUpdated.Broadcast();
	}
}

bool UInventoryComponent::AddItem(AItem* ItemToAdd)
{
	if (Items.Num() >= Capacity || !ItemToAdd)
	{
		return false;
	}

	ItemToAdd->OwningInventory = this;
	ItemToAdd->World = GetWorld();
	Items.Add(ItemToAdd);

	//ui update
	OnInventoryUpdated.Broadcast();

	return true;
}

bool UInventoryComponent::RemoveItem(AItem* ItemToRemove)
{
	if (ItemToRemove)
	{
		ItemToRemove->OwningInventory = nullptr;	
		ItemToRemove->World = nullptr;
		Items.RemoveSingle(ItemToRemove);

		OnInventoryUpdated.Broadcast();
		return true;
	}
	return false;
}


