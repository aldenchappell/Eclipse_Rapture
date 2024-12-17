#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetInventorySlot.generated.h"

class UImage;
class UTextBlock;
class AItem;
class UWidgetItemTooltip;
class USizeBox;
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

    ///** Clear the slot */
    //UFUNCTION(BlueprintCallable, Category = "Inventory Slot")
    //void SetSlotEmpty();

    ///** Set debug placeholder for empty or invalid items */
    //void SetDebugSlot();

    ///** Set this slot as occupied by an item */
    //void SetOccupied(AItem* Item);

    ///** Check if the slot is occupied */
    //UFUNCTION(BlueprintCallable, Category = "Inventory Slot")
    //bool IsOccupied() const;

    ///** Clear the slot and mark it as empty */
    //void ClearSlot();

    ///** Mark this slot as part of a multi-slot item */
    //void MarkAsPartOfMultiSlot();

    ///** Check if this slot is part of a multi-slot item */
    //bool IsPartOfMultiSlot() const;

    ///** Adjust slot size for multi-slot items */
    //void AdjustSlotSize(int32 RowSpan, int32 ColumnSpan);

    ///** Dynamically set slot size */
    //UFUNCTION(BlueprintCallable, Category = "Inventory Slot")
    //void SetSlotSize(float Width, float Height);

    //UFUNCTION(BlueprintCallable, Category = "Inventory Slot")
    //void HandleButtonClicked();

    UFUNCTION(BlueprintCallable, Category = "Inventory Slot")
    void ResetCreatedTooltips();

protected:
    virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
    virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
    virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
    virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

    //UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Inventory Slot | UI Settings")
    //float DefaultColumnSize = 50.f;  // Default width for one column

    //UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Inventory Slot | UI Settings")
    //float DefaultRowSize = 50.f;     // Default height for one row


    ///** UI Elements */
    //UPROPERTY(meta = (BindWidget))
    //class UButton* UseItemButton;

   /* UPROPERTY(meta = (BindWidget))
    UImage* ItemThumbnail;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* ItemQuantityText;*/

    //UPROPERTY(meta = (BindWidget))
    //USizeBox* SizeBox;

    ///** Debug placeholder image for invalid items */
    //UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Slot")
    //UTexture2D* DebugPlaceholderTexture;

    /** Tooltip class for displaying item details */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Slot")
    TSubclassOf<UWidgetItemTooltip> TooltipClass;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Inventory Properties")
    void InitializeSlot(UInventoryComponent* Inventory, float TileSize);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Inventory Properties")
    void CreateGridSegments();

//private:
    /** State of the slot */
    bool bIsOccupied = false;

    /** Reference to the item occupying the slot */
    AItem* OccupyingItem = nullptr;

    /** Tooltip widget instance */
    UWidgetItemTooltip* TooltipInstance = nullptr;
	TArray<UWidgetItemTooltip*> CreatedTooltips;
//
//    /** Whether this slot is part of a multi-slot item */
//    bool bIsPartOfMultiSlot = false;
};
