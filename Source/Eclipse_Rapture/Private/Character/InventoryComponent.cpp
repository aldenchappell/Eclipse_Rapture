#include "Character/InventoryComponent.h"
#include "Items/Item.h"
#include "UI/WidgetInventory.h" // Include for communication with the widget
#include "Engine/World.h"
#include "Kismet/KismetArrayLibrary.h"

UInventoryComponent::UInventoryComponent()
{
    Capacity = 20; // Capacity is no longer enforced directly
}

void UInventoryComponent::BeginPlay()
{
    Super::BeginPlay();

    // Ensure the InventoryItems array matches the grid size
    InventoryItems.Init(nullptr, Rows * Columns);

    // Ensure we have a valid owner
    bool retFlag;
    CheckForOwner(retFlag);
    if (retFlag) return;

    //InventoryItems.SetNum(Rows * Columns);

    // Populate items
    PopulateDefaultItems();

    OnInventoryUpdated.Broadcast(); // Notify the UI
}

void UInventoryComponent::CheckForOwner(bool& retFlag)
{
    retFlag = true;
    AActor* Owner = GetOwner();
    if (!Owner)
    {
        UE_LOG(LogTemp, Error, TEXT("InventoryComponent has no owner!"));
        return;
    }
    retFlag = false;
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}



void UInventoryComponent::PopulateDefaultItems()
{
    for (const FDefaultItem& DefaultItem : DefaultItems)
    {
        if (DefaultItem.Item)
        {
            for (int32 i = 0; i < DefaultItem.Quantity; ++i)
            {
                // Spawn an instance of the item
                AItem* SpawnedItem = GetWorld()->SpawnActor<AItem>(DefaultItem.Item);
                if (SpawnedItem)
                {
                    bool bSuccess = TryAddItem(SpawnedItem);
                    if (!bSuccess)
                    {
                        UE_LOG(LogTemp, Error, TEXT("Failed to add default item: %s"), *DefaultItem.Item->GetName());
                        SpawnedItem->Destroy(); // Clean up if not added
                    }
                }
                else
                {
                    UE_LOG(LogTemp, Error, TEXT("Failed to spawn default item: %s"), *DefaultItem.Item->GetName());
                }
            }
        }
    }
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
    UE_LOG(LogTemp, Warning, TEXT("GetItemInstance failed: No instance found for %s"), *ItemClass->GetName());
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

#pragma endregion

bool UInventoryComponent::TryAddItem_Implementation(AItem* Item)
{
    return false;
}

bool UInventoryComponent::IsRoomAvailable_Implementation(AItem* Item, int32 TopLeftTileIndex)
{
    return false;
}

bool UInventoryComponent::TryRemoveItem_Implementation(AItem* Item)
{
    return false;
}

void UInventoryComponent::IndexToTile_Implementation(int32 Index, FInventorySpaceRequirements& Requirements)
{
}

bool UInventoryComponent::IsTileValid_Implementation(FInventorySpaceRequirements Tiling)
{
    return false;
}

bool UInventoryComponent::GetItemAtIndex_Implementation(int32 Index, AItem*& Item)
{
    return false;
}

int32 UInventoryComponent::TileToIndex_Implementation(FInventorySpaceRequirements Tiling)
{
    return int32();
}

void UInventoryComponent::AddItemAt_Implementation(AItem* Item, int32 TopLeftIndex)
{
}

void UInventoryComponent::ForEachIndex_Implementation(AItem* Item, int32 TopLeftInventoryIndex, FInventorySpaceRequirements& Requirements)
{
}

void UInventoryComponent::GetAllItems_Implementation(TMap<AItem*, FInventorySpaceRequirements>& AllItems)
{
}
