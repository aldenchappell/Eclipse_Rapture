#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetInventory.generated.h"

class UWrapBox;
class UWidgetInventorySlot;
class UInventoryComponent;
class AItem;

/**
 * Inventory UI Widget
 */
UCLASS()
class ECLIPSE_RAPTURE_API UWidgetInventory : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Inventory UI")
    void InitializeInventory();


    // Function to refresh the inventory UI with updated inventory data
    UFUNCTION(BlueprintCallable, Category = "Inventory UI")
    void RefreshInventory(UInventoryComponent* PlayerInventory);

protected:
    virtual void NativeConstruct() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadonly, meta = (BindWidget))
    UWrapBox* InventoryWrapBox;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Grid")
    int32 Rows;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Grid")
    int32 Columns;

    // Widget class for individual inventory items
    UPROPERTY(EditDefaultsOnly,BlueprintReadonly, Category = "Inventory UI")
    TSubclassOf<class UWidgetInventorySlot> InventorySlotClass;


private:

    // Total slots for pre-population
    TArray<UWidgetInventorySlot*> InventorySlots;

    // Function to check if an item can fit in a specific grid position
    bool CanFitItemInSlot(int32 StartRow, int32 StartCol, int32 RowsRequired, int32 ColumnsRequired) const;

    // Function to place an item in the grid
    void PlaceItemInSlot(AItem* Item, int32 Quantity, int32 StartRow, int32 StartCol, int32 RowsRequired, int32 ColumnsRequired);

    
};
