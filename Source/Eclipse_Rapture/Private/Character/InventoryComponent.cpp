#include "Character/InventoryComponent.h"
#include "Items/Item.h"
#include "UI/WidgetInventory.h" // Include for communication with the widget
#include "Engine/World.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Items/ItemObject.h"
UInventoryComponent::UInventoryComponent()
{

}

void UInventoryComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UInventoryComponent::TryAddItem_Implementation(AItem* Item)
{
	return false;
}

bool UInventoryComponent::IsRoomAvailable_Implementation(AItem* Item, int32 TopLeftTileIndex)
{
	return false;
}

bool UInventoryComponent::TryRemoveItem_Implementation(AItem* Item)
{
	return false;
}

void UInventoryComponent::IndexToTile_Implementation(int32 Index, FInventorySpaceRequirements& Requirements)
{
}

bool UInventoryComponent::IsTileValid_Implementation(FInventorySpaceRequirements Tiling)
{
	return false;
}

bool UInventoryComponent::GetItemAtIndex_Implementation(int32 Index, AItem*& Item)
{
	return false;
}

int32 UInventoryComponent::TileToIndex_Implementation(FInventorySpaceRequirements Tiling)
{
	return int32();
}

void UInventoryComponent::AddItemAt_Implementation(AItem* Item, int32 TopLeftIndex)
{
}

void UInventoryComponent::ForEachIndex_Implementation(AItem* Item, int32 TopLeftInventoryIndex, FInventorySpaceRequirements& Requirements)
{
}

int32 UInventoryComponent::FindTotalAmountOfItem_Implementation(TSubclassOf<AItem> ItemClass, bool& ItemFound) const
{
	return int32();
}

bool UInventoryComponent::IsItemInInventory(TSubclassOf<AItem> ItemClass) const
{
	if (!ItemClass) // Check if the provided ItemClass is valid
	{
		UE_LOG(LogTemp, Warning, TEXT("IsItemInInventory: ItemClass is null"));
		return false;
	}

	
	UE_LOG(LogTemp, Log, TEXT("Checking item class: %s"), *ItemClass->GetName());
	// Check InventoryItems for a matching item class
	for (const AItem* Item : InventoryItems)
	{
		if (!Item)
		{
			UE_LOG(LogTemp, Warning, TEXT("Null item found in InventoryItems"));
			continue;
		}

		UE_LOG(LogTemp, Log, TEXT("Comparing with item: %s"), *Item->GetClass()->GetName());
		if (Item->GetClass() == ItemClass)
		{
			return true;
		}
	}


	// Check ItemCounts map for a matching item class
	for (const auto& Pair : ItemCounts)
	{
		if (Pair.Key == ItemClass) // No need for null checks since TMap should handle it
		{
			return true;
		}
	}

	return false;
}

