#pragma once

#include "Items/ItemTypes.h"
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
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemDescriptionText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemWeightText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemTypeText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly)
	TSubclassOf<class UWidgetItemUse> ItemUseWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UWidgetItemUse* ItemUseWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
	class UWidgetItemUse* OptionalSecondItemUseWidget;

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, Category = "Tooltip", meta = (ExposeOnSpawn = "true"))
	EUseImpactType UseImpactType;

	UPROPERTY(BlueprintReadWrite, Category = "Tooltip", meta = (ExposeOnSpawn = "true"))
	EMainItemUseDescriptionType MainItemUseDescriptionType;

	UPROPERTY(BlueprintReadWrite, Category = "Tooltip", meta = (ExposeOnSpawn = "true"))
	ESecondaryItemUseDescriptionType SecondaryItemUseDescriptionType;

	UPROPERTY(BlueprintReadWrite, Category = "Tooltip", meta = (ExposeOnSpawn = "true"))
	FText ItemDisplayName;

	

	UPROPERTY(BlueprintReadWrite, Category = "Tooltip", meta = (ExposeOnSpawn = "true"))
	FText ItemDescription;

	UPROPERTY(BlueprintReadWrite, Category = "Tooltip", meta = (ExposeOnSpawn = "true"))
	float ItemWeight;
};
