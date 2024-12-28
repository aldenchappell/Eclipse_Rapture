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

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Inventory Slot")
    void Refresh();

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

};
