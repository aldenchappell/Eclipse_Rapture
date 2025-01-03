#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetInventorySlot.generated.h"

class UImage;
class UTextBlock;
class AItem;
class UButton;
class UBorder;
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

    UFUNCTION(BlueprintCallable, Category = "Inventory Slot")
    void ResetCreatedTooltips();

    
protected:

#pragma region Mouse Events
    virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
    virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
    virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
    virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

#pragma endregion

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Slot")
    TSubclassOf<UWidgetItemTooltip> TooltipClass;

    UPROPERTY(BlueprintReadWrite, Category = "Item Data", meta = (ExposeOnSpawn = "true"))
    FName ItemID;

    UPROPERTY(BlueprintReadWrite, Category = "Item Data", meta = (ExposeOnSpawn = "true"))
    int32 Quantity;

    UPROPERTY(BlueprintReadWrite, Category = "Item Data", meta = (ExposeOnSpawn = "true"))
    TObjectPtr<class UInventoryComponent> InventoryComponent;

    UPROPERTY(BlueprintReadWrite, Category = "Item Data", meta = (ExposeOnSpawn = "true"))
    int32 SlotIndex;

    UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "UI Elements", meta = (BindWidget))
    TObjectPtr<USizeBox> SlotSizeBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "UI Elements", meta = (BindWidget))
    TObjectPtr<UButton> UseButton;

    UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "UI Elements", meta = (BindWidget))
    TObjectPtr<UBorder> UseButtonOuterBorder;

    UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "UI Elements", meta = (BindWidget))
    TObjectPtr<UBorder> UseButtonInnerBorder;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "UI Elements", meta = (BindWidget))
	TObjectPtr<class UOverlay> ContentsOverlay;

    UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "UI Elements", meta = (BindWidget))
    TObjectPtr<USizeBox> QuantitySizeBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "UI Elements", meta = (BindWidget))
    TObjectPtr<UBorder> QuantityOuterBorder;

    UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "UI Elements", meta = (BindWidget))
    TObjectPtr<UBorder> QuantityInnerBorder;

    //Exposed Pointers
    UPROPERTY(BlueprintReadonly, Category = "UI Elements", meta = (BindWidget))
    TObjectPtr<UImage> ItemThumbnail;

    UPROPERTY(BlueprintReadonly, Category = "UI Elements", meta = (BindWidget))
	TObjectPtr<UTextBlock> QuantityText;
private:

    /** Tooltip widget instance */
    UWidgetItemTooltip* TooltipInstance = nullptr;
	TArray<UWidgetItemTooltip*> CreatedTooltips;

public:

};
