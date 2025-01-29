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
    //Load inventory add add a listern to listen to the saveinventory function.
    LoadInventory();
	OnInventoryUpdated.AddDynamic(this, &UInventoryComponent::SaveInventory);

	OwningCharacter = Cast<AEclipseRaptureCharacter>(GetOwner());
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

bool UInventoryComponent::AddToInventory_Implementation(FName ItemID, int32 Quantity, int32& QuantityRemaining)
{
    return false;
}

void UInventoryComponent::TransferSlots_Implementation(int32 SourceIndex, UInventoryComponent* SourceInventory, int32 DestinationIndex)
{
}

bool UInventoryComponent::RemoveFromInventory_Implementation(int32 Index, bool RemoveWholeStack, bool IsConsumed)
{
    return false;
}

void UInventoryComponent::DropItem_Implementation(FName ItemID, int32 Quantity)
{
}

FItemData UInventoryComponent::GetItemData_Implementation(FName ItemID)
{
    return FItemData();
}

FVector UInventoryComponent::GetDropLocation_Implementation()
{
    return FVector();
}

bool UInventoryComponent::UseItem_Implementation(int32 Index)
{
    return false;
}

bool UInventoryComponent::QueryInventory_Implementation(FName ItemID, int32 Quantity, int32& FoundQuantity, int32& IndexFound)
{
    return false;
}

void UInventoryComponent::SaveInventory_Implementation()
{
}

void UInventoryComponent::LoadInventory_Implementation()
{
}

int32 UInventoryComponent::GetQuantityOfItem_Implementation()
{
    return int32();
}
