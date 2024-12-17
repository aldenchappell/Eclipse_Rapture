#include "Character/InventoryComponent.h"
#include "Items/Item.h"
#include "UI/WidgetInventory.h" // Include for communication with the widget
#include "Engine/World.h"

UInventoryComponent::UInventoryComponent()
{
    Capacity = 20; // Capacity is no longer enforced directly
}

void UInventoryComponent::BeginPlay()
{
    Super::BeginPlay();

    // Ensure we have a valid owner
    AActor* Owner = GetOwner();
    if (!Owner)
    {
        UE_LOG(LogTemp, Error, TEXT("InventoryComponent has no owner!"));
        return;
    }

    PopulateDefaultItems();
}

bool UInventoryComponent::AddItem(TSubclassOf<AItem> ItemClass)
{
    return AddItemAmount(ItemClass, 1);
}

bool UInventoryComponent::AddItemAmount(TSubclassOf<AItem> ItemClass, int32 Amount)
{
    if (!ItemClass || Amount <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("AddItemAmount failed: Invalid parameters."));
        return false;
    }

    AItem* DefaultItem = ItemClass->GetDefaultObject<AItem>();
    if (!DefaultItem)
    {
        UE_LOG(LogTemp, Warning, TEXT("AddItemAmount failed: Could not get default object for %s."), *ItemClass->GetName());
        return false;
    }

    int32 MaxStackSize = DefaultItem->MaxStackSize;
    int32* ExistingCount = Items.Find(ItemClass);

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
            Amount = TotalAmount - MaxStackSize; // Remaining amount
        }
    }
    else
    {
        Items.Add(ItemClass, FMath::Min(Amount, MaxStackSize));

        // Spawn an instance if adding a new item class
        AItem* NewItem = GetWorld()->SpawnActor<AItem>(ItemClass);
        if (NewItem)
        {
            ItemInstances.Add(NewItem);
            NewItem->OwningInventory = this;
            Amount -= FMath::Min(Amount, MaxStackSize); // Adjust remaining amount
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to spawn item instance for: %s"), *ItemClass->GetName());
        }
    }

    // Notify UI
    OnInventoryUpdated.Broadcast();
    return Amount == 0; // True if all items were added
}

bool UInventoryComponent::RemoveItem(TSubclassOf<AItem> ItemClass)
{
    return RemoveItemAmount(ItemClass, 1);
}

bool UInventoryComponent::RemoveItemAmount(TSubclassOf<AItem> ItemClass, int32 Amount)
{
    if (Amount <= 0) return false;

    int32* ExistingCount = Items.Find(ItemClass);

    if (ExistingCount && *ExistingCount > 0)
    {
        if (*ExistingCount > Amount)
        {
            *ExistingCount -= Amount;
        }
        else
        {
            Items.Remove(ItemClass);

            // Remove associated instance
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

        // Notify UI
        OnInventoryUpdated.Broadcast();
        return true;
    }

    return false;
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
    return nullptr;
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
        AItem* DefaultItem = ItemClass->GetDefaultObject<AItem>();
        return DefaultItem ? DefaultItem->MaxStackSize : 1;
    }
    return 1;
}

bool UInventoryComponent::CheckForItem(TSubclassOf<AItem> ItemClass)
{
    int32* ExistingCount = Items.Find(ItemClass);
    return ExistingCount && *ExistingCount > 0;
}

void UInventoryComponent::PopulateDefaultItems()
{
    // Add all default items to the inventory
    for (const FDefaultItem& DefaultItem : DefaultItems)
    {
        if (DefaultItem.ItemClass)
        {
            AddItemAmount(DefaultItem.ItemClass, DefaultItem.Quantity);
        }
    }

    // Notify the UI to update
    OnInventoryUpdated.Broadcast();
}