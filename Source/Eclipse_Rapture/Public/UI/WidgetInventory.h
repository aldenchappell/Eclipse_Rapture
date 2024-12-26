#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetInventory.generated.h"

class UUniformGridPanel;
class UWidgetInventoryGrid;
class UInventoryComponent;
class AItem;

UCLASS()
class ECLIPSE_RAPTURE_API UWidgetInventory : public UUserWidget
{
    GENERATED_BODY()

public:
   /* UFUNCTION(BlueprintCallable, Category = "Inventory UI")
    void InitializeInventory(UInventoryComponent* PlayerInventory);

    UFUNCTION(BlueprintCallable, Category = "Inventory UI")
    void RefreshInventory(UInventoryComponent* PlayerInventory);*/

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))//, meta = (ExposeOnSpawn = "true")))
    TObjectPtr<class UWidgetInventoryGrid> InventorySlot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory UI", meta = (ExposeOnSpawn = "true"))
    float TileSize;

protected:
    virtual void NativeConstruct() override;

    /*void GenerateGridSlots();
    bool CanPlaceItem(int32 StartRow, int32 StartCol, int32 RowsRequired, int32 ColumnsRequired) const;
    void PlaceItem(UWidgetInventorySlot* ItemSlot, int32 StartRow, int32 StartCol, int32 RowsRequired, int32 ColumnsRequired);

    void MarkSlotsAsOccupied(int32 StartRow, int32 StartCol, int32 RowsRequired, int32 ColumnsRequired);
    void ResetGrid();*/

    /*UPROPERTY(meta = (BindWidget))
    UUniformGridPanel* InventoryGrid;

    UPROPERTY(EditDefaultsOnly, Category = "Inventory UI")
    TSubclassOf<UWidgetInventorySlot> InventorySlotClass;

    UPROPERTY(EditDefaultsOnly, Category = "Inventory Settings")
    int32 TotalRows = 10;

    UPROPERTY(EditDefaultsOnly, Category = "Inventory Settings")
    int32 TotalColumns = 10;

    UFUNCTION(BlueprintCallable)
    void ClearInventorySlots();*/

    
	

private:
    //TArray<TArray<bool>> GridSlots; // Tracks slot occupancy

	//TArray<UWidgetInventorySlot*> InventorySlots; // All inventory slots

    
};
