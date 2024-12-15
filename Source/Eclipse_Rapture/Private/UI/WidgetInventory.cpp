#include "UI/WidgetInventory.h"
#include "UI/WidgetInventorySlot.h"
#include "Components/WrapBox.h"
#include "Character/InventoryComponent.h"
#include "Items/Item.h"

void UWidgetInventory::NativeConstruct()
{
    Super::NativeConstruct();

    // Initialize grid with current Rows and Columns values
    //InitializeInventory();
}

void UWidgetInventory::InitializeInventory()
{
    if (!InventoryWrapBox || !InventorySlotClass)
    {
        UE_LOG(LogTemp, Error, TEXT("InitializeInventory: InventoryWrapBox or InventorySlotClass is missing!"));
        return;
    }

    // Clear any previous slots
    InventoryWrapBox->ClearChildren();
    InventorySlots.Empty();

    // Calculate total slots
    int32 TotalSlots = Rows * Columns;
    UE_LOG(LogTemp, Log, TEXT("Spawning %d slots with Rows: %d, Columns: %d"), TotalSlots, Rows, Columns);

    // Spawn all slots
    for (int32 i = 0; i < TotalSlots; ++i)
    {
        UWidgetInventorySlot* SlotWidget = CreateWidget<UWidgetInventorySlot>(this, InventorySlotClass);
        if (SlotWidget)
        {
            InventorySlots.Add(SlotWidget);
            InventoryWrapBox->AddChild(SlotWidget);
            SlotWidget->SetSlotEmpty(); // Initialize all slots as empty
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to create InventorySlot at index %d"), i);
        }
    }
}

void UWidgetInventory::RefreshInventory(UInventoryComponent* PlayerInventory)
{
    if (!PlayerInventory || InventorySlots.Num() == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("RefreshInventory: Invalid PlayerInventory or InventorySlots."));
        return;
    }

    // Clear all slots visually
    for (UWidgetInventorySlot* InvSlots : InventorySlots)
    {
        if (InvSlots)
        {
            InvSlots->ClearSlot();
        }
    }

    // Loop through all items in the inventory
    for (const auto& ItemPair : PlayerInventory->Items)
    {
        AItem* ItemInstance = PlayerInventory->GetItemInstance(ItemPair.Key);

        if (ItemInstance)
        {
            const FInventorySpaceRequirements& Space = ItemInstance->InventorySpaceRequired;

            // Find a free slot for the item
            for (int32 Row = 0; Row < Rows; ++Row)
            {
                for (int32 Col = 0; Col < Columns; ++Col)
                {
                    if (CanFitItemInSlot(Row, Col, Space.RowsRequired, Space.ColumnsRequired))
                    {
                        PlaceItemInSlot(ItemInstance, ItemPair.Value, Row, Col, Space.RowsRequired, Space.ColumnsRequired);
                        goto NextItem; // Break when placed
                    }
                }
            }
        }
    NextItem:;
    }
}

void UWidgetInventory::PlaceItemInSlot(AItem* Item, int32 Quantity, int32 StartRow, int32 StartCol, int32 RowsRequired, int32 ColumnsRequired)
{
    for (int32 Row = 0; Row < RowsRequired; ++Row)
    {
        for (int32 Col = 0; Col < ColumnsRequired; ++Col)
        {
            int32 Index = (StartRow + Row) * Columns + (StartCol + Col);
            if (Index < InventorySlots.Num())
            {
                InventorySlots[Index]->SetItemDetails(Item, Quantity);
                InventorySlots[Index]->SetOccupied(Item);
            }
        }
    }
}


bool UWidgetInventory::CanFitItemInSlot(int32 StartRow, int32 StartCol, int32 RowsRequired, int32 ColumnsRequired) const
{
    // Check grid bounds
    if (StartRow + RowsRequired > Rows || StartCol + ColumnsRequired > Columns)
    {
        UE_LOG(LogTemp, Warning, TEXT("CanFitItemInSlot: Item exceeds grid bounds at Row: %d, Col: %d"), StartRow, StartCol);
        return false;
    }

    // Check for occupied slots
    for (int32 Row = 0; Row < RowsRequired; ++Row)
    {
        for (int32 Col = 0; Col < ColumnsRequired; ++Col)
        {
            int32 Index = (StartRow + Row) * Columns + (StartCol + Col);
            if (Index < InventorySlots.Num() && InventorySlots[Index]->IsOccupied())
            {
                UE_LOG(LogTemp, Warning, TEXT("CanFitItemInSlot: Slot at Index %d is already occupied."), Index);
                return false;
            }
        }
    }
    return true;
}