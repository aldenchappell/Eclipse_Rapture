#include "UI/WidgetInventorySlot.h"
#include "UI/WidgetItemTooltip.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Items/Item.h"
#include "Components/SizeBox.h"
#include "Components/Button.h"

void UWidgetInventorySlot::SetItemDetails(AItem* Item, int32 Quantity)
{
    if (Item && Item->ThumbnailTexture)
    {
        ItemThumbnail->SetBrushFromTexture(Item->ThumbnailTexture);
        ItemQuantityText->SetText(FText::AsNumber(Quantity));
        UseItemButton->SetIsEnabled(true); // Enable button if item is valid
    }
    else
    {
        SetDebugSlot();
    }

    bIsOccupied = true;
    OccupyingItem = Item;
}

void UWidgetInventorySlot::SetSlotEmpty()
{
    ItemThumbnail->SetBrushFromTexture(nullptr);
    ItemQuantityText->SetText(FText::GetEmpty());
    UseItemButton->SetIsEnabled(false); // Disable button when slot is empty

    bIsOccupied = false;
    OccupyingItem = nullptr;
}


void UWidgetInventorySlot::SetDebugSlot() 
{
    if (DebugPlaceholderTexture)
    {
        ItemThumbnail->SetBrushFromTexture(DebugPlaceholderTexture);
        //ItemNameText->SetText(FText::FromString("DEBUG ITEM"));
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
    bIsPartOfMultiSlot = false; // Reset multi-slot status
}

void UWidgetInventorySlot::HandleButtonClicked()
{
    if (OccupyingItem)
    {
        // Call item use logic (assuming Use function exists in AItem)
        OccupyingItem->Use(Cast<AEclipseRaptureCharacter>(GetOwningPlayerPawn()));
        UE_LOG(LogTemp, Log, TEXT("Item %s was clicked and used!"), *OccupyingItem->GetName());
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

void UWidgetInventorySlot::SetSlotSize(float Width, float Height)
{
    if (SizeBox)
    {
        SizeBox->SetWidthOverride(Width);
        SizeBox->SetHeightOverride(Height);
    }
}


void UWidgetInventorySlot::AdjustSlotSize(int32 RowSpan, int32 ColumnSpan)
{
    if (ItemThumbnail)
    {
        FVector2D NewSize = FVector2D(50.f * ColumnSpan, 50.f * RowSpan); // Base slot size = 50x50
        ItemThumbnail->SetDesiredSizeOverride(NewSize);
    }
}

void UWidgetInventorySlot::MarkAsPartOfMultiSlot()
{
    bIsPartOfMultiSlot = true;
}

bool UWidgetInventorySlot::IsPartOfMultiSlot() const
{
    return bIsPartOfMultiSlot;
}

