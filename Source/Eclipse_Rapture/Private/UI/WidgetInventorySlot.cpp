#include "UI/WidgetInventorySlot.h"
#include "UI/WidgetItemTooltip.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Items/Item.h"

void UWidgetInventorySlot::SetItemDetails(AItem* Item, int32 Quantity)
{
    if (Item && Item->ThumbnailTexture)
    {
        // Update UI for valid item
        ItemThumbnail->SetBrushFromTexture(Item->ThumbnailTexture);
        ItemQuantityText->SetText(FText::AsNumber(Quantity));
        ItemNameText->SetText(Item->GetItemDisplayName());
    }
    else
    {
        // Use debug placeholder for invalid items
        SetDebugSlot();
    }

    bIsOccupied = true;
    OccupyingItem = Item;
}

void UWidgetInventorySlot::SetSlotEmpty()
{
    ItemThumbnail->SetBrushFromTexture(nullptr);
    ItemQuantityText->SetText(FText::GetEmpty());
    ItemNameText->SetText(FText::GetEmpty());
    bIsOccupied = false;
    OccupyingItem = nullptr;
}

void UWidgetInventorySlot::SetDebugSlot()
{
    if (DebugPlaceholderTexture)
    {
        ItemThumbnail->SetBrushFromTexture(DebugPlaceholderTexture);
        ItemNameText->SetText(FText::FromString("DEBUG ITEM"));
        ItemQuantityText->SetText(FText::FromString("N/A"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("SetDebugSlot: DebugPlaceholderTexture is missing."));
        SetSlotEmpty(); // If no debug texture, fallback to empty state
    }

    bIsOccupied = true;
}

void UWidgetInventorySlot::SetOccupied(AItem* Item)
{
    bIsOccupied = true;
    OccupyingItem = Item;
}

bool UWidgetInventorySlot::IsOccupied() const
{
    return bIsOccupied;
}

void UWidgetInventorySlot::ClearSlot()
{
    SetSlotEmpty();
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
        }
    }
}

void UWidgetInventorySlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
    if (TooltipInstance)
    {
        TooltipInstance->RemoveFromParent();
        TooltipInstance = nullptr;
    }
}
