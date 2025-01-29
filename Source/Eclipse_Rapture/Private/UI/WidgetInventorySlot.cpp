#include "UI/WidgetInventorySlot.h"
#include "Blueprint/DragDropOperation.h"




void UWidgetInventorySlot::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    //if (!bIsOccupied)
    //{
    //    // Change color to indicate valid drop
    //    //ItemThumbnail->SetColorAndOpacity(FLinearColor::Green);
    //}
}



 void UWidgetInventorySlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
   // if (OccupyingItem && TooltipClass)
   // {
   //     // Create and display the tooltip
   //     TooltipInstance = CreateWidget<UWidgetItemTooltip>(GetWorld(), TooltipClass);
   //     if (TooltipInstance)
   //     {
   //         TooltipInstance->AddToViewport();
   //         TooltipInstance->InitializeTooltip(OccupyingItem); // Custom function in tooltip to show item details
			//CreatedTooltips.AddUnique(TooltipInstance);
   //     }
   // }
}

void UWidgetInventorySlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
    /*if (TooltipInstance)
    {
        TooltipInstance->RemoveFromParent();
        TooltipInstance = nullptr;
		CreatedTooltips.Remove(TooltipInstance);
    }*/
}

FReply UWidgetInventorySlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    /*if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton) && OccupyingItem)
    {
        return FReply::Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
    }*/
    return FReply::Unhandled();
}

void UWidgetInventorySlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
    //if (OccupyingItem)
    //{
    //    UDragDropOperation* DragOperation = NewObject<UDragDropOperation>();
    //    DragOperation->DefaultDragVisual = this; // Use slot widget as drag visual
    //    DragOperation->Payload = this;

    //    OutOperation = DragOperation;

    //    //SetSlotEmpty(); // Temporarily clear slot during drag
    //}
}

bool UWidgetInventorySlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    /*if (InOperation && InOperation->Payload)
    {
        UWidgetInventorySlot* DraggedSlot = Cast<UWidgetInventorySlot>(InOperation->Payload);
        if (DraggedSlot && DraggedSlot->OccupyingItem)
        {
            SetItemDetails(DraggedSlot->OccupyingItem, 1);
            return true;
        }
    }*/
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
