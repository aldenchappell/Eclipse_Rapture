// EclipseRaptureBuildingItem.cpp

#include "Items/Item.h"
#include "Character/InventoryComponent.h"
#include "Building/BuildingTypes.h"
#include "Building/EclipseRaptureBuildingItem.h"

AEclipseRaptureBuildingItem::AEclipseRaptureBuildingItem()
{
    PrimaryActorTick.bCanEverTick = false;
	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Building Mesh"));
	RootComponent = BuildingMesh;
   
}

void AEclipseRaptureBuildingItem::BeginPlay()
{
    Super::BeginPlay();

}

void AEclipseRaptureBuildingItem::UpgradeBuilding_Implementation(FUpgradeInfo UpgradeInfo)
{
    if (!UpgradeInfo.UpgraderInventory || !Materials.IsValidIndex(UpgradeInfo.UpgradeLevel))
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid upgrade information or materials index."));
        return;
    }

    // Get the required items for the upgrade
    TArray<TSubclassOf<AItem>> RequiredItems = GetRequiredUpgradeItems_Implementation(UpgradeInfo);

    // Check if all required items are present in the player's inventory
    for (TSubclassOf<AItem> ItemClass : RequiredItems)
    {
        if (!UpgradeInfo.UpgraderInventory->CheckForItem(ItemClass))
        {
            UE_LOG(LogTemp, Warning, TEXT("Player is missing required item: %s"), *ItemClass->GetName());
            return;  // Exit if any item is missing
        }
    }

    // Remove the required items from the inventory
    for (TSubclassOf<AItem> ItemClass : RequiredItems)
    {
        UpgradeInfo.UpgraderInventory->RemoveItem(ItemClass);
        UE_LOG(LogTemp, Log, TEXT("Removed item: %s"), *ItemClass->GetName());
    }

    // Update the building's material
    UStaticMeshComponent* Mesh = FindComponentByClass<UStaticMeshComponent>();
    if (Mesh && Materials.IsValidIndex(UpgradeInfo.UpgradeLevel))
    {
        Mesh->SetMaterial(0, Materials[UpgradeInfo.UpgradeLevel]);
        UE_LOG(LogTemp, Log, TEXT("Building upgraded to level %d"), UpgradeInfo.UpgradeLevel);
    }
}


TArray<TSubclassOf<AItem>> AEclipseRaptureBuildingItem::GetRequiredUpgradeItems_Implementation(FUpgradeInfo UpgradeInfo)
{
    if (RequiredUpgradeItems.Contains(UpgradeInfo.UpgradeLevel))
    {
        return RequiredUpgradeItems[UpgradeInfo.UpgradeLevel].RequiredItems;
    }
    return TArray<TSubclassOf<AItem>>(); // Return an empty array if the upgrade level is invalid
}
