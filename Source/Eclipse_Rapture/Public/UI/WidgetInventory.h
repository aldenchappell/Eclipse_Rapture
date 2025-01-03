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


protected:
    virtual void NativeConstruct() override;

};
