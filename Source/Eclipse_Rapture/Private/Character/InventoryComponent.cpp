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
    AActor* Owner = GetOwner();
    if (!Owner)
    {
        UE_LOG(LogTemp, Error, TEXT("InventoryComponent has no owner!"));
        return;
    }

    InventoryItems.SetNum(Rows * Columns);

    // Populate items
    PopulateDefaultItems();

    OnInventoryUpdated.Broadcast(); // Notify the UI
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


#pragma region New Inventory Functions

bool UInventoryComponent::TryAddItem(AItem* Item)
{
    if (!Item)
    {
        UE_LOG(LogTemp, Warning, TEXT("TryAddItem: Invalid Item (nullptr)."));
        return false;
    }

    UE_LOG(LogTemp, Log, TEXT("TryAddItem: Attempting to add item %s to the inventory."), *Item->GetName());

    // Find available space
    for (int32 TopLeftIndex = 0; TopLeftIndex < InventoryItems.Num(); ++TopLeftIndex)
    {
        if (IsRoomAvailable(Item, TopLeftIndex))
        {
            AddItemAt(Item, TopLeftIndex);
            UE_LOG(LogTemp, Log, TEXT("TryAddItem: Successfully added item %s at index %d."), *Item->GetName(), TopLeftIndex);
            return true;
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("TryAddItem: Failed to add item %s. No available space found."), *Item->GetName());
    return false;
}


bool UInventoryComponent::IsRoomAvailable(AItem* Item, int32 TopLeftTileIndex)
{
    if (!Item || TopLeftTileIndex < 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("IsRoomAvailable: Invalid Item or TopLeftTileIndex."));
        return false;
    }

    FInventorySpaceRequirements Requirements = Item->InventorySpaceRequired;

    for (int32 Row = 0; Row < Requirements.RowsRequired; ++Row)
    {
        for (int32 Column = 0; Column < Requirements.ColumnsRequired; ++Column)
        {
            int32 CurrentIndex = TopLeftTileIndex + Column + (Row * Columns);

            if (!InventoryItems.IsValidIndex(CurrentIndex) || InventoryItems[CurrentIndex] != nullptr)
            {
                return false; // Tile is out of bounds or already occupied
            }
        }
    }

    return true; // Space is available
}




//bool UInventoryComponent::IsRoomAvailable(AItem* Item, int32 TopLeftTileIndex)
//{
//    if (!Item)
//    {
//        UE_LOG(LogTemp, Warning, TEXT("IsRoomAvailable: Invalid Item!"));
//        return false;
//    }
//
//    // Use ForEachIndex to retrieve space requirements and iterate over required indices
//    FInventorySpaceRequirements SpaceRequirements = ForEachIndex(Item, TopLeftTileIndex);
//
//    // Check each index provided by ForEachIndex
//    for (int32 Row = 0; Row < SpaceRequirements.RowsRequired; ++Row)
//    {
//        for (int32 Column = 0; Column < SpaceRequirements.ColumnsRequired; ++Column)
//        {
//            int32 CurrentTileIndex = TopLeftTileIndex + Column + (Row * Columns);
//
//            // Ensure tile is within bounds
//            if (!IsTileValid(FInventorySpaceRequirements(Row, Column)))
//            {
//                return false;
//            }
//
//            // Check if the tile is occupied
//            AItem* ExistingItem = nullptr;
//            if (GetItemAtIndex(CurrentTileIndex, ExistingItem) && ExistingItem != nullptr)
//            {
//                return false; // Tile is already occupied
//            }
//        }
//    }
//
//    return true; // Room is available
//}



FInventorySpaceRequirements UInventoryComponent::IndexToTile(int32 Index)
{
    FInventorySpaceRequirements Tile;

    if (Columns == 0) // Prevent division by zero
    {
        UE_LOG(LogTemp, Error, TEXT("IndexToTile: Columns is zero, cannot calculate tile position!"));
        return Tile;
    }

    // Calculate rows and columns based on the index
    Tile.RowsRequired = Index / Columns;   // Division for row calculation
    Tile.ColumnsRequired = Index % Columns; // Modulo for column calculation

    return Tile;
}



bool UInventoryComponent::IsTileValid(FInventorySpaceRequirements Tiling)
{
    return (Tiling.RowsRequired >= 0 && Tiling.ColumnsRequired >= 0 &&
            Tiling.RowsRequired < Rows && Tiling.ColumnsRequired < Columns);
}


bool UInventoryComponent::GetItemAtIndex(int32 Index, AItem*& Item)
{
    if (InventoryItems.IsValidIndex(Index))
    {
        Item = InventoryItems[Index];
        return true;
    }
    Item = nullptr;
    return false;
}


int32 UInventoryComponent::TileToIndex(FInventorySpaceRequirements Tiling)
{
    if (Columns == 0) return -1; // Prevent division by zero

    return Tiling.RowsRequired + Tiling.ColumnsRequired * Columns;
}



void UInventoryComponent::AddItemAt(AItem* Item, int32 TopLeftIndex)
{
    if (!Item || TopLeftIndex < 0 || !InventoryItems.IsValidIndex(TopLeftIndex))
    {
        UE_LOG(LogTemp, Warning, TEXT("AddItemAt: Invalid Item or TopLeftIndex %d"), TopLeftIndex);
        return;
    }

    FInventorySpaceRequirements Requirements = Item->InventorySpaceRequired;

    // Place the item in the grid
    for (int32 Row = 0; Row < Requirements.RowsRequired; ++Row)
    {
        for (int32 Column = 0; Column < Requirements.ColumnsRequired; ++Column)
        {
            int32 CurrentIndex = TopLeftIndex + Column + (Row * Columns);

            if (InventoryItems.IsValidIndex(CurrentIndex))
            {
                InventoryItems[CurrentIndex] = Item;
            }
        }
    }

    Item->OwningInventory = this;
    OnInventoryUpdated.Broadcast();
}



FInventorySpaceRequirements UInventoryComponent::ForEachIndex(AItem* Item, int32 TopLeftInventoryIndex)
{
    FInventorySpaceRequirements SpaceRequirements;

    if (!Item || TopLeftInventoryIndex < 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("ForEachIndex: Invalid Item or TopLeftIndex."));
        return SpaceRequirements;
    }

    // Get space requirements from the item
    int32 RowsRequired = Item->InventorySpaceRequired.RowsRequired;
    int32 ColumnsRequired = Item->InventorySpaceRequired.ColumnsRequired;

    SpaceRequirements.RowsRequired = RowsRequired;
    SpaceRequirements.ColumnsRequired = ColumnsRequired;

    int32 StartRow = TopLeftInventoryIndex / Columns;
    int32 StartColumn = TopLeftInventoryIndex % Columns;

    UE_LOG(LogTemp, Log, TEXT("ForEachIndex: Starting at Row %d, Column %d"), StartRow, StartColumn);

    // Loop through the required rows and columns
    for (int32 Row = 0; Row < RowsRequired; ++Row)
    {
        for (int32 Column = 0; Column < ColumnsRequired; ++Column)
        {
            int32 CurrentRow = StartRow + Row;
            int32 CurrentColumn = StartColumn + Column;

            // Ensure we are within bounds
            if (CurrentRow >= 0 && CurrentRow < Rows && CurrentColumn >= 0 && CurrentColumn < Columns)
            {
                int32 CurrentIndex = (CurrentRow * Columns) + CurrentColumn;
                UE_LOG(LogTemp, Log, TEXT("ForEachIndex: Iterating Index %d (Row %d, Column %d)"), CurrentIndex, CurrentRow, CurrentColumn);
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("ForEachIndex: Index out of bounds at Row %d, Column %d"), CurrentRow, CurrentColumn);
            }
        }
    }

    return SpaceRequirements;
}



#pragma endregion