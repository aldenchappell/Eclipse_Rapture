#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetInventorySlot.generated.h"

class UImage;
class UTextBlock;
class AItem;
class UWidgetItemTooltip;

/**
 * Inventory Slot UI Widget
 */
UCLASS()
class ECLIPSE_RAPTURE_API UWidgetInventorySlot : public UUserWidget
{
    GENERATED_BODY()

public:
    /** Set item details in the slot */
    UFUNCTION(BlueprintCallable, Category = "Inventory Slot")
    void SetItemDetails(AItem* Item, int32 Quantity);

    /** Clear the slot */
    UFUNCTION(BlueprintCallable, Category = "Inventory Slot")
    void SetSlotEmpty();

    /** Set debug placeholder for empty or invalid items */
    void SetDebugSlot();

    /** Set this slot as occupied by an item */
    void SetOccupied(AItem* Item);

    /** Check if the slot is occupied */
    UFUNCTION(BlueprintCallable, Category = "Inventory Slot")
    bool IsOccupied() const;

    /** Clear the slot and mark it as empty */
    void ClearSlot();

protected:
    virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

    /** UI Elements */
    UPROPERTY(meta = (BindWidget))
    UImage* ItemThumbnail;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* ItemQuantityText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* ItemNameText;

    /** Debug placeholder image for invalid items */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Slot")
    UTexture2D* DebugPlaceholderTexture;

    /** Tooltip class for displaying item details */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Slot")
    TSubclassOf<UWidgetItemTooltip> TooltipClass;

private:
    /** State of the slot */
    bool bIsOccupied = false;

    /** Reference to the item occupying the slot */
    AItem* OccupyingItem = nullptr;

    /** Tooltip widget instance */
    UWidgetItemTooltip* TooltipInstance = nullptr;
};
