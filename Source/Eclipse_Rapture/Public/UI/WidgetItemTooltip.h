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
	UTextBlock* ItemTypeText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly)
	TSubclassOf<class UWidgetItemUse> ItemUseWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UWidgetItemUse* ItemUseWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	class UWidgetItemUse* OptionalSecondItemUseWidget;

	virtual void NativeConstruct() override;
};
