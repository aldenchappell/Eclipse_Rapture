#include "UI/WidgetItemTooltip.h"
#include "Components/TextBlock.h"
#include "Items/Item.h"
#include "UI/WidgetItemUse.h"

void UWidgetItemTooltip::NativeConstruct()
{
	Super::NativeConstruct();

	// Initialize with empty values to avoid displaying stale data
	if (ItemNameText)
		ItemNameText->SetText(FText::FromString("No Item"));

	if (ItemDescriptionText)
		ItemDescriptionText->SetText(FText::FromString("No description available."));

	if (ItemWeightText)
		ItemWeightText->SetText(FText::FromString("Weight: 0"));

	if (ItemTypeText)
		ItemTypeText->SetText(FText::FromString("Type: Unknown"));
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
		if (!Item->ItemDisplayName.IsEmpty())
		{
			ItemNameText->SetText(Item->GetItemDisplayName());
		}
		else
		{
			ItemNameText->SetText(FText::FromString("No Item"));
		}
	}

	if (ItemDescriptionText)
	{
		if (!Item->ItemDescription.IsEmpty())
		{
			ItemDescriptionText->SetText(Item->ItemDescription);
		}
		else
		{
			ItemDescriptionText->SetText(FText::FromString("No description available."));
		}
	}

	if (ItemWeightText)
	{
		if (Item->ItemWeight > 0.0f)
		{
			FString WeightString = FString::Printf(TEXT("Weight: %.2f"), Item->ItemWeight);
			ItemWeightText->SetText(FText::FromString(WeightString));
		}
		else
		{
			ItemWeightText->SetText(FText::FromString("Weight: Unknown"));
		}
	}

	if (ItemTypeText)
	{
		if (Item->GetUsecaseType() != EUsecaseType::EUT_None) // Example condition, adjust as needed
		{
			FString ItemTypeString = FString::Printf(TEXT("Type: %s"),
													 *UEnum::GetDisplayValueAsText(Item->GetUsecaseType()).ToString());
			ItemTypeText->SetText(FText::FromString(ItemTypeString));
		}
		else
		{
			ItemTypeText->SetText(FText::FromString("Type: Unknown"));
		}
	}

	// Optional Widgets
	if (ItemUseWidget)
	{
		ItemUseWidget->SetItemUseDetails(Item);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemUseWidget is null."));
	}

	if (OptionalSecondItemUseWidget)
	{
		OptionalSecondItemUseWidget->SetItemUseDetails(Item);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OptionalSecondItemUseWidget is null."));
	}

	UE_LOG(LogTemp, Log, TEXT("Tooltip Initialized for Item: %s"), *Item->GetName());
}
