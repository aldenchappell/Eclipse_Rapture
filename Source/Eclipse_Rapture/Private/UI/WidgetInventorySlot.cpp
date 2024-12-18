#include "UI/WidgetInventorySlot.h"
#include "UI/WidgetItemTooltip.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Items/Item.h"
#include "Components/SizeBox.h"
#include "Components/Button.h"
#include "Blueprint/DragDropOperation.h"



void UWidgetInventorySlot::CreateGridSegments_Implementation()
{
}

void UWidgetInventorySlot::InitializeSlot_Implementation(UInventoryComponent* Inventory, float TileSize)
{
}

void UWidgetInventorySlot::SetItemDetails(AItem* Item, int32 Quantity)
{
    if (!Item) //|| !ItemThumbnail)
    {
        UE_LOG(LogTemp, Error, TEXT("SetItemDetails: Invalid parameters or unbound widgets!"));
        return;
    }

    //ItemThumbnail->SetBrushFromTexture(Item->ThumbnailTexture);
    //ItemQuantityText->SetText(FText::AsNumber(Quantity));
   // AdjustSlotSize(Item->InventorySpaceRequired.RowsRequired, Item->InventorySpaceRequired.ColumnsRequired);
   //     UseItemButton->SetIsEnabled(true);

   //     AdjustSlotSize(Item->InventorySpaceRequired.RowsRequired, Item->InventorySpaceRequired.ColumnsRequired);

        UE_LOG(LogTemp, Log, TEXT("Item set: %s, Quantity: %d, Rows: %d, Columns: %d"),
               *Item->GetName(), Quantity, Item->InventorySpaceRequired.RowsRequired, Item->InventorySpaceRequired.ColumnsRequired);

    bIsOccupied = true;
    OccupyingItem = Item;
}

void UWidgetInventorySlot::Refresh_Implementation()
{
}

 

 void UWidgetInventorySlot::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    if (!bIsOccupied)
    {
        // Change color to indicate valid drop
        //ItemThumbnail->SetColorAndOpacity(FLinearColor::Green);
    }
}

 void UWidgetInventorySlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (OccupyingItem && TooltipClass)
    {
        // Create and display the tooltip
        TooltipInstance = CreateWidget<UWidgetItemTooltip>(GetWorld(), TooltipClass);
        if (TooltipInstance)
        {
            TooltipInstance->AddToViewport();
            TooltipInstance->InitializeTooltip(OccupyingItem); // Custom function in tooltip to show item details
			CreatedTooltips.AddUnique(TooltipInstance);
        }
    }
}

void UWidgetInventorySlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
    if (TooltipInstance)
    {
        TooltipInstance->RemoveFromParent();
        TooltipInstance = nullptr;
		CreatedTooltips.Remove(TooltipInstance);
    }
}

FReply UWidgetInventorySlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton) && OccupyingItem)
    {
        return FReply::Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
    }
    return FReply::Unhandled();
}

void UWidgetInventorySlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
    if (OccupyingItem)
    {
        UDragDropOperation* DragOperation = NewObject<UDragDropOperation>();
        DragOperation->DefaultDragVisual = this; // Use slot widget as drag visual
        DragOperation->Payload = this;

        OutOperation = DragOperation;

        //SetSlotEmpty(); // Temporarily clear slot during drag
    }
}

bool UWidgetInventorySlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    if (InOperation && InOperation->Payload)
    {
        UWidgetInventorySlot* DraggedSlot = Cast<UWidgetInventorySlot>(InOperation->Payload);
        if (DraggedSlot && DraggedSlot->OccupyingItem)
        {
            SetItemDetails(DraggedSlot->OccupyingItem, 1);
            return true;
        }
    }
    return false;
}


void UWidgetInventorySlot::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    // Reset the color or visual feedback for the slot
   /* if (ItemThumbnail)
    {
        ItemThumbnail->SetColorAndOpacity(FLinearColor::White);
    }*/
}

void UWidgetInventorySlot::ResetCreatedTooltips()
{
    if (CreatedTooltips.Num() <= 0) return;

	for (UWidgetItemTooltip* Tooltip : CreatedTooltips)
	{
		if (Tooltip)
		{
			Tooltip->RemoveFromParent();
			Tooltip = nullptr;
            CreatedTooltips.Empty();
		}
	}
   
}

//#pragma region Old Functions


//
//void UWidgetInventorySlot::SetSlotEmpty()
//{
//    ItemThumbnail->SetBrushFromTexture(nullptr);
//    ItemQuantityText->SetText(FText::GetEmpty());
//    UseItemButton->SetIsEnabled(false); // Disable button when slot is empty
//
//    bIsOccupied = false;
//    OccupyingItem = nullptr;
//}
//
//
//void UWidgetInventorySlot::SetDebugSlot() 
//{
//    if (DebugPlaceholderTexture)
//    {
//        ItemThumbnail->SetBrushFromTexture(DebugPlaceholderTexture);
//        //ItemNameText->SetText(FText::FromString("DEBUG ITEM"));
//        ItemQuantityText->SetText(FText::FromString("N/A"));
//    }
//    else
//    {
//        UE_LOG(LogTemp, Warning, TEXT("SetDebugSlot: DebugPlaceholderTexture is missing."));
//        SetSlotEmpty(); // If no debug texture, fallback to empty state
//    }
//
//    bIsOccupied = true;
//}
//
//void UWidgetInventorySlot::SetOccupied(AItem* Item)
//{
//    bIsOccupied = true;
//    OccupyingItem = Item;
//}
//
//
//bool UWidgetInventorySlot::IsOccupied() const
//{
//    return bIsOccupied;
//}
//
//void UWidgetInventorySlot::ClearSlot()
//{
//    SetSlotEmpty();
//    bIsPartOfMultiSlot = false; // Reset multi-slot status
//}
//
//void UWidgetInventorySlot::HandleButtonClicked()
//{
//    if (OccupyingItem)
//    {
//        // Call item use logic (assuming Use function exists in AItem)
//        OccupyingItem->Use(Cast<AEclipseRaptureCharacter>(GetOwningPlayerPawn()));
//        UE_LOG(LogTemp, Log, TEXT("Item %s was clicked and used!"), *OccupyingItem->GetName());
//    }
//}
//

//
//void UWidgetInventorySlot::SetSlotSize(float Width, float Height)
//{
//    if (SizeBox)
//    {
//        SizeBox->SetWidthOverride(Width);
//        SizeBox->SetHeightOverride(Height);
//        UseItemButton->SetRenderScale(FVector2D(Width, Height));
//        UE_LOG(LogTemp, Log, TEXT("SetSlotSize: Width: %.1f, Height: %.1f"), Width, Height);
//    }
//}
//
//
//
//
//void UWidgetInventorySlot::AdjustSlotSize(int32 RowSpan, int32 ColumnSpan)
//{
//    if (SizeBox)
//    {
//        float SlotWidth = 50.f * ColumnSpan;
//        float SlotHeight = 50.f * RowSpan;
//        SizeBox->SetWidthOverride(SlotWidth);
//        SizeBox->SetHeightOverride(SlotHeight);
//		UseItemButton->SetRenderScale(FVector2D(ColumnSpan, RowSpan));
//    }
//    UE_LOG(LogTemp, Log, TEXT("Slot size set to Width: %.1f, Height: %.1f"), 50.f * ColumnSpan, 50.f * RowSpan);
//}
//
//
//
//
//void UWidgetInventorySlot::MarkAsPartOfMultiSlot()
//{
//    bIsPartOfMultiSlot = true;
//}
//
//bool UWidgetInventorySlot::IsPartOfMultiSlot() const
//{
//    return bIsPartOfMultiSlot;
//}
//

//#pragma endregion