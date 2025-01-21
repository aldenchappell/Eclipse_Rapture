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

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<class UWidgetInventorySlot> InventorySlot;

    UFUNCTION(BlueprintCallable, Category = "Inventory Slot")
    void ResetCreatedTooltips();

protected:
    virtual void NativeConstruct() override;

    /** Tooltip widget instance */

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory Slot")
    TArray<class UWidgetItemTooltip*> CreatedTooltips;
};
