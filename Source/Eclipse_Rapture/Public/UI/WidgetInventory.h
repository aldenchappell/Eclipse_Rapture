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
    bool CanPlaceItem(int32 StartRow, int32 StartCol, int32 RowsRequired, int32 ColumnsRequired) const;
    void PlaceItem(UWidgetInventorySlot* ItemSlot, int32 StartRow, int32 StartCol, int32 RowsRequired, int32 ColumnsRequired);

    void MarkSlotsAsOccupied(int32 StartRow, int32 StartCol, int32 RowsRequired, int32 ColumnsRequired);
    void ResetGrid();

    UPROPERTY(meta = (BindWidget))
    UUniformGridPanel* InventoryGrid;

    UPROPERTY(EditDefaultsOnly, Category = "Inventory UI")
    TSubclassOf<UWidgetInventorySlot> InventorySlotClass;

    UPROPERTY(EditDefaultsOnly, Category = "Inventory Settings")
    int32 TotalRows = 10;

    UPROPERTY(EditDefaultsOnly, Category = "Inventory Settings")
    int32 TotalColumns = 10;

private:
    TArray<TArray<bool>> GridSlots; // Tracks slot occupancy
};
