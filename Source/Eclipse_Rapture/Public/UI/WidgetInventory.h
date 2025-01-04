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

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    TObjectPtr<class UWidgetInventorySlot> InventorySlot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory UI", meta = (ExposeOnSpawn = "true"))
    float TileSize;

protected:
    virtual void NativeConstruct() override;

};
