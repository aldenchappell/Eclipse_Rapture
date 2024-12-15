#include "UI/WidgetItemTooltip.h"
#include "Components/TextBlock.h"
#include "Items/Item.h"

void UWidgetItemTooltip::NativeConstruct()
{
	Super::NativeConstruct();

	// Initialize with empty values to avoid displaying stale data
	if (ItemNameText) ItemNameText->SetText(FText::FromString("No Item"));
	if (ItemDescriptionText) ItemDescriptionText->SetText(FText::FromString("No description available."));
	if (ItemWeightText) ItemWeightText->SetText(FText::FromString("Weight: 0"));
	if (ItemQuantityText) ItemQuantityText->SetText(FText::FromString("Quantity: 0"));
}

void UWidgetItemTooltip::InitializeTooltip(AItem* Item)
{
	if (!Item)
	{
		UE_LOG(LogTemp, Warning, TEXT("InitializeTooltip: Item is null."));
		return;
	}

	// Update tooltip text with item details
	if (ItemNameText)
	{
		ItemNameText->SetText(Item->GetItemDisplayName());
	}

	if (ItemDescriptionText)
	{
		ItemDescriptionText->SetText(Item->ItemDescription.IsEmpty() ?
									 FText::FromString("No description available.") :
									 Item->ItemDescription);
	}

	if (ItemWeightText)
	{
		FString WeightString = FString::Printf(TEXT("Weight: %.2f"), Item->ItemWeight);
		ItemWeightText->SetText(FText::FromString(WeightString));
	}

	if (ItemQuantityText)
	{
		FString QuantityString = FString::Printf(TEXT("Quantity: %d"), Item->MaxStackSize);
		ItemQuantityText->SetText(FText::FromString(QuantityString));
	}

	UE_LOG(LogTemp, Log, TEXT("Tooltip Initialized for Item: %s"), *Item->GetName());
}
