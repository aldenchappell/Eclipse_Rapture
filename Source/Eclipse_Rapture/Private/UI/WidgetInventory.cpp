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
        UE_LOG(LogTemp, Error, TEXT("GenerateGridSlots: InventoryGridPanel not assigned!"));
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
                UUniformGridSlot* GridSlot = InventoryGridPanel->AddChildToUniformGrid(SlotWidget, Row, Col);
                if (GridSlot)
                {
                    GridSlot->SetHorizontalAlignment(HAlign_Left);
                    GridSlot->SetVerticalAlignment(VAlign_Top);
                }
                SlotWidget->SetSlotEmpty();

                // Debug the slot placement
                UE_LOG(LogTemp, Log, TEXT("Generated Slot at Row: %d, Col: %d"), Row, Col);
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to create slot widget at Row: %d, Col: %d"), Row, Col);
            }
        }
    }
    UE_LOG(LogTemp, Log, TEXT("Generated %d rows x %d columns of slots"), Rows, Columns);
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
    if (!PlayerInventory)
    {
        UE_LOG(LogTemp, Warning, TEXT("RefreshInventory: PlayerInventory is null"));
        return;
    }

    InventoryGridPanel->ClearChildren();
    ResetGridOccupancy();

    UE_LOG(LogTemp, Log, TEXT("Refreshing Inventory. Total Items: %d"), PlayerInventory->Items.Num());

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

                            // Debug item placement
                            UE_LOG(LogTemp, Log, TEXT("Placed Item: %s at Row: %d, Col: %d, Size: [%d x %d]"),
                                   *ItemInstance->GetName(), Row, Col, Space.RowsRequired, Space.ColumnsRequired);
                        }
                        else
                        {
                            UE_LOG(LogTemp, Error, TEXT("Failed to create item slot for %s"), *ItemInstance->GetName());
                        }
                        goto NextItem;
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
                UE_LOG(LogTemp, Warning, TEXT("Cannot Fit Item: Slot [%d, %d] is occupied or out of bounds"),
                       StartRow + Row, StartCol + Col);
                return false;
            }
        }
    }
    return true;
}


void UWidgetInventory::PlaceItem(UWidgetInventorySlot* ItemSlot, int32 Row, int32 Col, int32 RowsRequired, int32 ColumnsRequired)
{
    UUniformGridSlot* GridSlot = InventoryGridPanel->AddChildToUniformGrid(ItemSlot, Row, Col);

    if (GridSlot)
    {
        GridSlot->SetHorizontalAlignment(HAlign_Left);
        GridSlot->SetVerticalAlignment(VAlign_Top);

        // Adjust slot size
        ItemSlot->SetSlotSize(50.f * ColumnsRequired, 50.f * RowsRequired);
    }
}



void UWidgetInventory::MarkSlotsAsOccupied(int32 StartRow, int32 StartCol, int32 RowsRequired, int32 ColumnsRequired)
{
    for (int32 Row = 0; Row < RowsRequired; ++Row)
    {
        for (int32 Col = 0; Col < ColumnsRequired; ++Col)
        {
            SlotOccupancyGrid[StartRow + Row][StartCol + Col] = true;
            UE_LOG(LogTemp, Log, TEXT("Marked Slot Occupied at [%d, %d]"), StartRow + Row, StartCol + Col);
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
