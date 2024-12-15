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
    AActor* Owner = GetOwner();
    if (Owner)
    {
        UE_LOG(LogTemp, Warning, TEXT("InventoryComponent owner: %s"), *Owner->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("InventoryComponent has no owner!"));
    }

    // Add default items
    for (const FDefaultItem& DefaultItem : DefaultItems)
    {
        if (DefaultItem.ItemClass)
        {
            AddItemAmount(DefaultItem.ItemClass, DefaultItem.Quantity);
        }
    }

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
    if (!ItemClass || Amount <= 0 || Items.Num() >= Capacity)
    {
        UE_LOG(LogTemp, Error, TEXT("AddItemAmount failed: ItemClass=%s, Amount=%d, CurrentItems=%d, Capacity=%d"),
               *GetNameSafe(ItemClass), Amount, Items.Num(), Capacity);
        return false;
    }

    int32* ExistingCount = Items.Find(ItemClass);
    int32 MaxStackSize = GetMaxStackSize(ItemClass);

    if (ExistingCount)
    {
        int32 TotalAmount = *ExistingCount + Amount;
        if (TotalAmount <= MaxStackSize)
        {
            *ExistingCount = TotalAmount;
        }
        else
        {
            *ExistingCount = MaxStackSize;
            return false; // Couldn't add the full amount due to stack limit
        }
    }
    else
    {
        int32 AmountToAdd = FMath::Min(Amount, MaxStackSize);
        Items.Add(ItemClass, AmountToAdd);

        // Spawn an instance if adding a new item class
        AItem* NewItem = GetWorld()->SpawnActor<AItem>(ItemClass);
        if (NewItem)
        {
            ItemInstances.Add(NewItem);
            NewItem->OwningInventory = this;
            UE_LOG(LogTemp, Warning, TEXT("Spawned item instance: %s"), *NewItem->GetName());
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to spawn item instance for: %s"), *ItemClass->GetName());
        }
    }

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
        if (Item)
        {
            UE_LOG(LogTemp, Warning, TEXT("MaxStackSize for %s is %d"), *ItemClass->GetName(), Item->MaxStackSize);
            return FMath::Max(1, static_cast<int32>(Item->MaxStackSize));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("GetDefaultObject failed for %s"), *ItemClass->GetName());
        }
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