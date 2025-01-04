#include "Character/InventoryComponent.h"
#include "Items/Item.h"
#include "Engine/World.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Structures/FInventoryTypes.h"
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

void UInventoryComponent::FindSlot_Implementation(FName ItemID)
{

}

bool UInventoryComponent::CreateNewStack_Implementation(FName ItemID, int32 Quantity)
{
    return false;
}

bool UInventoryComponent::IsEmptySlotAvailable_Implementation(int32& EmptyIndex)
{
    return false;
}

void UInventoryComponent::AddToExistingStack_Implementation(int32 Index, int32 Quantity)
{
}

bool UInventoryComponent::FindInventorySlot_Implementation(FName ItemID, int32& SlotIndex)
{
    return false;
}

int32 UInventoryComponent::GetMaxStackSize_Implementation(FName ItemID)
{
    return int32();
}

bool UInventoryComponent::RemoveFromInventory_Implementation(FName ItemID, int32 Quantity, int32& QuantityRemaining)
{
    return false;
}

bool UInventoryComponent::AddToInventory_Implementation(FName ItemID, int32 Quantity, int32& QuantityRemaining)
{
    return false;
}

void UInventoryComponent::TransferSlots_Implementation(int32 SourceIndex, UInventoryComponent* SourceInventory, int32 DestinationIndex)
{
}
