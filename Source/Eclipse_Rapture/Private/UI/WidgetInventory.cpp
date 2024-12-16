#include "UI/WidgetInventory.h"
#include "UI/WidgetInventorySlot.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Character/InventoryComponent.h"
#include "Items/Item.h"

void UWidgetInventory::NativeConstruct()
{
    Super::NativeConstruct();
    GenerateGridSlots();
}

void UWidgetInventory::GenerateGridSlots()
{
    if (!InventoryGridPanel)
    {
        UE_LOG(LogTemp, Error, TEXT("InventoryGridPanel not assigned!"));
        return;
    }

    InventoryGridPanel->ClearChildren();
    ResetGridOccupancy();

    for (int32 Row = 0; Row < Rows; ++Row)
    {
        for (int32 Col = 0; Col < Columns; ++Col)
        {
            UWidgetInventorySlot* SlotWidget = CreateWidget<UWidgetInventorySlot>(this, InventorySlotClass);
            if (SlotWidget)
            {
                InventoryGridPanel->AddChildToUniformGrid(SlotWidget, Row, Col);
                SlotWidget->SetSlotEmpty(); // Initialize as empty
            }
        }
    }
}

void UWidgetInventory::InitializeInventory(UInventoryComponent* PlayerInventory)
{
    if (!InventoryGridPanel || !InventorySlotClass || !PlayerInventory)
    {
        UE_LOG(LogTemp, Error, TEXT("InitializeInventory: Missing components!"));
        return;
    }

    RefreshInventory(PlayerInventory);
}

void UWidgetInventory::RefreshInventory(UInventoryComponent* PlayerInventory)
{
    if (!PlayerInventory) return;

    InventoryGridPanel->ClearChildren();
    ResetGridOccupancy();

    for (const auto& ItemPair : PlayerInventory->Items)
    {
        AItem* ItemInstance = PlayerInventory->GetItemInstance(ItemPair.Key);
        if (ItemInstance)
        {
            const FInventorySpaceRequirements& Space = ItemInstance->InventorySpaceRequired;
            for (int32 Row = 0; Row < Rows; ++Row)
            {
                for (int32 Col = 0; Col < Columns; ++Col)
                {
                    if (CanFitItem(Row, Col, Space.RowsRequired, Space.ColumnsRequired))
                    {
                        UWidgetInventorySlot* ItemSlot = CreateWidget<UWidgetInventorySlot>(this, InventorySlotClass);
                        if (ItemSlot)
                        {
                            ItemSlot->SetItemDetails(ItemInstance, ItemPair.Value);
                            PlaceItem(ItemSlot, Row, Col, Space.RowsRequired, Space.ColumnsRequired);
                            MarkSlotsAsOccupied(Row, Col, Space.RowsRequired, Space.ColumnsRequired);
                        }
                        goto NextItem; // Break nested loops
                    }
                }
            }
        }
    NextItem:;
    }
}

bool UWidgetInventory::CanFitItem(int32 StartRow, int32 StartCol, int32 RowsRequired, int32 ColumnsRequired) const
{
    for (int32 Row = 0; Row < RowsRequired; ++Row)
    {
        for (int32 Col = 0; Col < ColumnsRequired; ++Col)
        {
            if (StartRow + Row >= Rows || StartCol + Col >= Columns || SlotOccupancyGrid[StartRow + Row][StartCol + Col])
            {
                return false; // Out of bounds or occupied
            }
        }
    }
    return true;
}

void UWidgetInventory::PlaceItem(UWidgetInventorySlot* ItemSlot, int32 Row, int32 Col, int32 RowsRequired, int32 ColumnsRequired)
{
    // Add the item slot to the UniformGridPanel
    UUniformGridSlot* GridSlot = InventoryGridPanel->AddChildToUniformGrid(ItemSlot, Row, Col);

    if (GridSlot)
    {
        // Optionally configure the GridSlot (alignment, padding, etc.)
        GridSlot->SetHorizontalAlignment(HAlign_Fill);
        GridSlot->SetVerticalAlignment(VAlign_Fill);

        // Dynamically set size of the slot
        if (ItemSlot)
        {
            // Ensure the sizebox exists in the WidgetInventorySlot
            ItemSlot->SetSlotSize(50.f * ColumnsRequired, 50.f * RowsRequired);
        }

        UE_LOG(LogTemp, Log, TEXT("Placed item at Row: %d, Col: %d with size [%d x %d]"), Row, Col, RowsRequired, ColumnsRequired);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to place item in grid at Row: %d, Col: %d"), Row, Col);
    }
}

void UWidgetInventory::MarkSlotsAsOccupied(int32 StartRow, int32 StartCol, int32 RowsRequired, int32 ColumnsRequired)
{
    for (int32 Row = 0; Row < RowsRequired; ++Row)
    {
        for (int32 Col = 0; Col < ColumnsRequired; ++Col)
        {
            SlotOccupancyGrid[StartRow + Row][StartCol + Col] = true;
        }
    }
}

void UWidgetInventory::ResetGridOccupancy()
{
    SlotOccupancyGrid.Empty();
    for (int32 Row = 0; Row < Rows; ++Row)
    {
        TArray<bool> RowArray;
        RowArray.Init(false, Columns);
        SlotOccupancyGrid.Add(RowArray);
    }
}