#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetInventory.generated.h"

class UUniformGridPanel;
class UWidgetInventorySlot;
class UInventoryComponent;
class AItem;

UCLASS()
class ECLIPSE_RAPTURE_API UWidgetInventory : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Inventory UI")
    void InitializeInventory(UInventoryComponent* PlayerInventory);

    UFUNCTION(BlueprintCallable, Category = "Inventory UI")
    void RefreshInventory(UInventoryComponent* PlayerInventory);

protected:
    virtual void NativeConstruct() override;

    void GenerateGridSlots();
    bool CanFitItem(int32 StartRow, int32 StartCol, int32 RowsRequired, int32 ColumnsRequired) const;
    void PlaceItem(UWidgetInventorySlot* ItemSlot, int32 Row, int32 Col, int32 RowsRequired, int32 ColumnsRequired);

    void MarkSlotsAsOccupied(int32 StartRow, int32 StartCol, int32 RowsRequired, int32 ColumnsRequired);
    void ResetGridOccupancy();

    UPROPERTY(meta = (BindWidget))
    UUniformGridPanel* InventoryGridPanel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Grid")
    int32 Rows = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Grid")
    int32 Columns = 10;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory UI")
    TSubclassOf<UWidgetInventorySlot> InventorySlotClass;

private:
    TArray<TArray<bool>> SlotOccupancyGrid; // 2D array for tracking slot occupancy
};