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

#pragma region New Inventory Functions and Variables


bool UInventoryComponent::TryAddItem_Implementation(UItemObject* ItemObject)
{
    return false;
}

bool UInventoryComponent::IsRoomAvailable_Implementation(UItemObject* ItemObject, int32 TopLeftTileIndex)
{
    return false;
}

bool UInventoryComponent::TryRemoveItem_Implementation(UItemObject* ItemObject)
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

bool UInventoryComponent::GetItemAtIndex_Implementation(int32 Index, UItemObject*& Item)
{
    return false;
}

int32 UInventoryComponent::TileToIndex_Implementation(FInventorySpaceRequirements Tiling)
{
    return int32();
}

void UInventoryComponent::AddItemAt_Implementation(UItemObject* ItemObject, int32 TopLeftIndex)
{
}

void UInventoryComponent::ForEachIndex_Implementation(UItemObject* ItemObject, int32 TopLeftInventoryIndex, FInventorySpaceRequirements& Requirements)
{
}

#pragma endregion