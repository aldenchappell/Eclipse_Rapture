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
    if (!InventoryGrid)
    {
        UE_LOG(LogTemp, Error, TEXT("GenerateGridSlots: InventoryGrid is null!"));
        return;
    }

    if (!InventorySlotClass)
    {
        UE_LOG(LogTemp, Error, TEXT("GenerateGridSlots: InventorySlotClass is not set!"));
        return;
    }

    InventoryGrid->ClearChildren();
    ResetGrid();

    for (int32 Row = 0; Row < TotalRows; ++Row)
    {
        for (int32 Col = 0; Col < TotalColumns; ++Col)
        {
            UWidgetInventorySlot* SlotWidget = CreateWidget<UWidgetInventorySlot>(this, InventorySlotClass);
            if (SlotWidget)
            {
                InventoryGrid->AddChildToUniformGrid(SlotWidget, Row, Col);
                SlotWidget->SetSlotEmpty();
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to create slot widget at Row %d, Col %d"), Row, Col);
            }
        }
    }
}


void UWidgetInventory::InitializeInventory(UInventoryComponent* PlayerInventory)
{
    if (!InventoryGrid)
    {
        UE_LOG(LogTemp, Error, TEXT("InitializeInventory: InventoryGrid is null!"));
        return;
    }

    if (!InventorySlotClass)
    {
        UE_LOG(LogTemp, Error, TEXT("InitializeInventory: InventorySlotClass is not set!"));
        return;
    }

    if (!PlayerInventory)
    {
        UE_LOG(LogTemp, Error, TEXT("InitializeInventory: PlayerInventory is null!"));
        return;
    }

    UE_LOG(LogTemp, Log, TEXT("Initializing Inventory..."));

    // Reset grid and rebuild
    ResetGrid();
    InventoryGrid->ClearChildren();
    GenerateGridSlots();
    RefreshInventory(PlayerInventory);
}


void UWidgetInventory::RefreshInventory(UInventoryComponent* PlayerInventory)
{
    if (!PlayerInventory || !InventoryGrid) return;

    ResetGrid();
    InventoryGrid->ClearChildren();

    for (const auto& ItemPair : PlayerInventory->Items)
    {
        AItem* Item = PlayerInventory->GetItemInstance(ItemPair.Key);
        if (Item)
        {
            int32 Rows = Item->InventorySpaceRequired.RowsRequired;
            int32 Columns = Item->InventorySpaceRequired.ColumnsRequired;

            for (int32 Row = 0; Row < TotalRows; ++Row)
            {
                for (int32 Col = 0; Col < TotalColumns; ++Col)
                {
                    if (CanPlaceItem(Row, Col, Rows, Columns))
                    {
                        UWidgetInventorySlot* ItemSlot = CreateWidget<UWidgetInventorySlot>(this, InventorySlotClass);
                        PlaceItem(ItemSlot, Row, Col, Rows, Columns);
                        ItemSlot->SetItemDetails(Item, ItemPair.Value);
                        MarkSlotsAsOccupied(Row, Col, Rows, Columns);
						InventorySlots.AddUnique(ItemSlot);
                        goto NextItem;
                    }
                }
            }
        }
    NextItem:;
    }
}



bool UWidgetInventory::CanPlaceItem(int32 StartRow, int32 StartCol, int32 RowsRequired, int32 ColumnsRequired) const
{
    for (int32 Row = 0; Row < RowsRequired; ++Row)
    {
        for (int32 Col = 0; Col < ColumnsRequired; ++Col)
        {
            if (StartRow + Row >= TotalRows || StartCol + Col >= TotalColumns || GridSlots[StartRow + Row][StartCol + Col])
                return false; // Slot occupied or out of bounds
        }
    }
    return true;
}

void UWidgetInventory::PlaceItem(UWidgetInventorySlot* ItemSlot, int32 StartRow, int32 StartCol, int32 RowsRequired, int32 ColumnsRequired)
{
    UUniformGridSlot* GridSlot = InventoryGrid->AddChildToUniformGrid(ItemSlot, StartRow, StartCol);
    if (GridSlot)
    {
        GridSlot->SetHorizontalAlignment(HAlign_Fill);
        GridSlot->SetVerticalAlignment(VAlign_Fill);

        // Resize slot dynamically
        ItemSlot->SetSlotSize(50.f * ColumnsRequired, 50.f * RowsRequired);
    }
}

void UWidgetInventory::MarkSlotsAsOccupied(int32 StartRow, int32 StartCol, int32 RowsRequired, int32 ColumnsRequired)
{
    for (int32 Row = 0; Row < RowsRequired; ++Row)
    {
        for (int32 Col = 0; Col < ColumnsRequired; ++Col)
        {
            GridSlots[StartRow + Row][StartCol + Col] = true;
        }
    }
}

void UWidgetInventory::ResetGrid()
{
    GridSlots.Empty();
    for (int32 Row = 0; Row < TotalRows; ++Row)
    {
        TArray<bool> RowArray;
        RowArray.Init(false, TotalColumns);
        GridSlots.Add(RowArray);
    }
}

void UWidgetInventory::ClearInventorySlots()
{
	for (UWidgetInventorySlot* InvSlot : InventorySlots)
	{
		if (InvSlot)
		{
            InvSlot->ResetCreatedTooltips();
            InventorySlots.Empty();
		}
	}
}
