#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetItemUse.generated.h"

// Forward Declaration
class AItem;

/**
 * Tooltip UI Widget to display item details
 */
UCLASS()
class ECLIPSE_RAPTURE_API UWidgetItemUse : public UUserWidget
{
    GENERATED_BODY()

public:
    // Set the details of the item to display in the tooltip
    UFUNCTION(BlueprintCallable, Category = "Item Tooltip")
    void SetItemUseDetails(AItem* Item);

protected:
    /** UI Elements */
    UPROPERTY(meta = (BindWidget))
    class UImage* UseThumbnail;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* ItemUseText;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* ItemImpactText;

    

    // Optional debug placeholder
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tooltip")
    UTexture2D* DebugPlaceholderTexture;
};
