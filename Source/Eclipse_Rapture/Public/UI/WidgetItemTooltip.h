#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetItemTooltip.generated.h"

class UTextBlock;
class AItem;

/**
 * Tooltip widget to display item details
 */
UCLASS()
class ECLIPSE_RAPTURE_API UWidgetItemTooltip : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Initialize the tooltip with item details */
	UFUNCTION(BlueprintCallable, Category = "Tooltip")
	void InitializeTooltip(AItem* Item);

protected:
	/** UI Elements */
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemNameText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemDescriptionText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemWeightText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemQuantityText;

	virtual void NativeConstruct() override;
};
