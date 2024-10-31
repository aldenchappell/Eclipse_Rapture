#include "Character/InventoryComponent.h"
#include "Items/Item.h"
#include "Engine/World.h"

UInventoryComponent::UInventoryComponent()
{
    Capacity = 20;
}

void UInventoryComponent::BeginPlay()
{
    Super::BeginPlay();

    //Spawn default items from their classes
    for (auto& ItemClass : DefaultItems)
    {
        if (ItemClass)
        {
            // Spawn the item in the world
            AItem* NewItem = GetWorld()->SpawnActor<AItem>(ItemClass);
            if (NewItem)
            {
                AddItem(NewItem);
            }
        }
    }

    //UI update
    OnInventoryUpdated.Broadcast();
}

bool UInventoryComponent::AddItem(AItem* ItemToAdd)
{
    if (Items.Num() >= Capacity || !ItemToAdd)
    {
        return false;
    }

    ItemToAdd->OwningInventory = this;
    Items.Add(ItemToAdd);

    //UI update
    OnInventoryUpdated.Broadcast();

    return true;
}

bool UInventoryComponent::RemoveItem(AItem* ItemToRemove)
{
    if (ItemToRemove)
    {
        ItemToRemove->OwningInventory = nullptr;
        Items.RemoveSingle(ItemToRemove);

        OnInventoryUpdated.Broadcast();
        return true;
    }
    return false;
}

bool UInventoryComponent::CheckForItem(TSubclassOf<AItem> ItemClass)
{
    for (AItem* Item : Items)
    {
        if (Item && Item->IsA(ItemClass))
        {
            return true; //Found at least one item of this type
        }
    }
    return false; //No items of this type found
}

int32 UInventoryComponent::GetItemAmount(TSubclassOf<AItem> ItemClass)
{
    //track how many items of this type are found
    int32 Count = 0;

    for (AItem* Item : Items)
    {
        if (Item && Item->IsA(ItemClass))
        {
			++Count; //Found an item of this type, increment count
        }
    }

    return Count;
}
