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

    // Spawn default items from their classes
    for (const FDefaultItem& DefaultItem : DefaultItems)
    {
        if (DefaultItem.ItemClass)  // Check if the item class is valid
        {
            // Add the specified amount of the item to the inventory
            AddItemAmount(DefaultItem.ItemClass, DefaultItem.Quantity);
        }
    }

    // UI update
    OnInventoryUpdated.Broadcast();
}


bool UInventoryComponent::AddItem(TSubclassOf<AItem> ItemClass)
{
    if (!ItemClass || Items.Num() >= Capacity)
    {
        return false;
    }

    int32* ExistingCount = Items.Find(ItemClass);
    int32 MaxStackSize = GetMaxStackSize(ItemClass);

    if (ExistingCount)
    {
        if (*ExistingCount < MaxStackSize)
        {
            (*ExistingCount)++;
        }
        else
        {
            return false; // Item can't be added if it exceeds stack size
        }
    }
    else
    {
        Items.Add(ItemClass, 1);

        // Spawn an instance if adding a new item class
        AItem* NewItem = GetWorld()->SpawnActor<AItem>(ItemClass);
        if (NewItem)
        {
            ItemInstances.Add(NewItem);
            NewItem->OwningInventory = this; // Optional: Set ownership
        }
    }

    // UI update
    OnInventoryUpdated.Broadcast();

    return true;
}

bool UInventoryComponent::AddItemAmount(TSubclassOf<AItem> ItemClass, int32 Amount)
{
    // Check if ItemClass is valid, the amount is greater than 0, and capacity allows it
    if (!ItemClass || Amount <= 0 || Items.Num() >= Capacity)
    {
        return false;
    }

    int32* ExistingCount = Items.Find(ItemClass);
    int32 MaxStackSize = GetMaxStackSize(ItemClass);

    if (ExistingCount)
    {
        int32 TotalAmount = *ExistingCount + Amount;

        // Check if the total amount exceeds the max stack size
        if (TotalAmount <= MaxStackSize)
        {
            *ExistingCount = TotalAmount; // Simply add to the current count
        }
        else
        {
            *ExistingCount = MaxStackSize; // Limit to max stack size
            return false; // Couldn't add the full amount due to stack limit
        }
    }
    else
    {
        // If item doesn't exist, add a new entry with the lesser of Amount or MaxStackSize
        int32 AmountToAdd = FMath::Min(Amount, MaxStackSize);
        Items.Add(ItemClass, AmountToAdd);

        // Spawn an instance if adding a new item class
        AItem* NewItem = GetWorld()->SpawnActor<AItem>(ItemClass);
        if (NewItem)
        {
            ItemInstances.Add(NewItem);
            NewItem->OwningInventory = this; // Optional: Set ownership
        }
    }

    // Notify UI or other systems about the update
    OnInventoryUpdated.Broadcast();

    return true;
}

bool UInventoryComponent::RemoveItem(TSubclassOf<AItem> ItemClass)
{
    int32* ExistingCount = Items.Find(ItemClass);

    if (ExistingCount && *ExistingCount > 0)
    {
        if (*ExistingCount > 1)
        {
            (*ExistingCount)--;
        }
        else
        {
            Items.Remove(ItemClass);

            // Remove an instance if count reaches zero
            for (int32 i = 0; i < ItemInstances.Num(); i++)
            {
                if (ItemInstances[i] && ItemInstances[i]->IsA(ItemClass))
                {
                    ItemInstances[i]->Destroy();
                    ItemInstances.RemoveAt(i);
                    break;
                }
            }
        }

        // UI update
        OnInventoryUpdated.Broadcast();
        return true;
    }

    return false;
}

bool UInventoryComponent::RemoveItemAmount(TSubclassOf<AItem> ItemClass, int32 Amount)
{
    if (Amount <= 0) return false;  // Ensure valid amount

    int32* ExistingCount = Items.Find(ItemClass);

    if (ExistingCount && *ExistingCount > 0)
    {
        if (*ExistingCount > Amount)
        {
            *ExistingCount -= Amount;
        }
        else
        {
            Items.Remove(ItemClass);  // Remove item completely if amount is greater or equal to existing count

            // Also destroy instance if available
            for (int32 i = 0; i < ItemInstances.Num(); i++)
            {
                if (ItemInstances[i] && ItemInstances[i]->IsA(ItemClass))
                {
                    ItemInstances[i]->Destroy();
                    ItemInstances.RemoveAt(i);
                    break;
                }
            }
        }

        OnInventoryUpdated.Broadcast();  // Notify UI or other systems about the update
        return true;
    }

    return false;
}


bool UInventoryComponent::CheckForItem(TSubclassOf<AItem> ItemClass)
{
    int32* ExistingCount = Items.Find(ItemClass);
    return ExistingCount && *ExistingCount > 0;
}

int32 UInventoryComponent::GetItemAmount(TSubclassOf<AItem> ItemClass)
{
    int32* ExistingCount = Items.Find(ItemClass);
    return ExistingCount ? *ExistingCount : 0;
}

int32 UInventoryComponent::GetMaxStackSize(TSubclassOf<AItem> ItemClass) const
{
    if (ItemClass)
    {
        AItem* Item = ItemClass->GetDefaultObject<AItem>();
        return Item ? FMath::Max(1, static_cast<int32>(Item->MaxStackSize)) : 1; // Default to 1 if MaxStackSize is 0
    }
    return 1;
}

AItem* UInventoryComponent::GetItemInstance(TSubclassOf<AItem> ItemClass)
{
    for (AItem* Item : ItemInstances)
    {
        if (Item && Item->IsA(ItemClass))
        {
            return Item;
        }
    }
    return nullptr; // No matching instance found
}


