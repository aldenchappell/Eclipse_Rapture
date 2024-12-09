#include "Building/EclipseRaptureBuildingItem.h"
#include "Items/Item.h"
#include "Character/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"

AEclipseRaptureBuildingItem::AEclipseRaptureBuildingItem()
{
    PrimaryActorTick.bCanEverTick = false;
    BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Building Mesh"));
    RootComponent = BuildingMesh;
    CurrentUpgradeLevel = 0;
    MaxUpgradeLevel = 3; // Example
    bShowDebugMessages = true;
}

void AEclipseRaptureBuildingItem::BeginPlay()
{
    Super::BeginPlay();
	OnBuildingUpgrade.AddDynamic(this, &AEclipseRaptureBuildingItem::UpgradeBuilding);
}

void AEclipseRaptureBuildingItem::UpgradeBuilding_Implementation(FUpgradeInfo UpgradeInfo)
{
    if (!UpgradeInfo.UpgraderInventory)
    {
        UE_LOG(LogTemp, Error, TEXT("Upgrade failed: Invalid inventory."));
        return;
    }

    if (CurrentUpgradeLevel >= MaxUpgradeLevel)
    {
        FString Message = FString::Printf(TEXT("Building is fully upgraded (Level: %d)."), CurrentUpgradeLevel);
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, Message);
        UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
        return;
    }

    if (!UpgradeRequirements.Contains(CurrentUpgradeLevel + 1))
    {
        UE_LOG(LogTemp, Error, TEXT("Upgrade failed: Missing requirements for level %d."), CurrentUpgradeLevel + 1);
        return;
    }

    FUpgradeRequirements Requirements = UpgradeRequirements[CurrentUpgradeLevel + 1];
    if (Requirements.RequiredItems.Num() != Requirements.RequiredQuantities.Num())
    {
        UE_LOG(LogTemp, Error, TEXT("Upgrade failed: Items and quantities mismatch for level %d."), CurrentUpgradeLevel + 1);
        return;
    }

    // Validate required items and quantities
    for (int32 Index = 0; Index < Requirements.RequiredItems.Num(); ++Index)
    {
        TSubclassOf<AItem> ItemClass = Requirements.RequiredItems[Index];
        int32 RequiredQuantity = Requirements.RequiredQuantities[Index];

        if (!UpgradeInfo.UpgraderInventory->CheckForItem(ItemClass) ||
            UpgradeInfo.UpgraderInventory->GetItemAmount(ItemClass) < RequiredQuantity)
        {
            FString MissingItemMessage = FString::Printf(
                TEXT("Missing %d of item: %s"),
                RequiredQuantity,
                *ItemClass->GetName()
            );
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, MissingItemMessage);
            UE_LOG(LogTemp, Warning, TEXT("%s"), *MissingItemMessage);
            return;
        }
    }

    // Deduct required items
    for (int32 Index = 0; Index < Requirements.RequiredItems.Num(); ++Index)
    {
        TSubclassOf<AItem> ItemClass = Requirements.RequiredItems[Index];
        int32 QuantityToRemove = Requirements.RequiredQuantities[Index];

        UpgradeInfo.UpgraderInventory->RemoveItemAmount(ItemClass, QuantityToRemove);
        FString RemovedItemMessage = FString::Printf(
            TEXT("Removed %d of item: %s"),
            QuantityToRemove,
            *ItemClass->GetName()
        );
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, RemovedItemMessage);
        UE_LOG(LogTemp, Log, TEXT("%s"), *RemovedItemMessage);
    }

    // Upgrade material
    if (BuildingMesh && Materials.IsValidIndex(CurrentUpgradeLevel + 1))
    {
        BuildingMesh->SetMaterial(0, Materials[CurrentUpgradeLevel + 1]);
        FString UpgradeMessage = FString::Printf(TEXT("Building upgraded to level %d."), CurrentUpgradeLevel + 1);
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, UpgradeMessage);
        UE_LOG(LogTemp, Log, TEXT("%s"), *UpgradeMessage);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to update material for level %d."), CurrentUpgradeLevel + 1);
    }

    // Increment level
    CurrentUpgradeLevel++;
}

TArray<TSubclassOf<AItem>> AEclipseRaptureBuildingItem::GetRequiredUpgradeItems_Implementation(FUpgradeInfo UpgradeInfo)
{
    TArray<TSubclassOf<AItem>> RequiredItems;

    if (UpgradeRequirements.Contains(UpgradeInfo.UpgradeLevel))
    {
        RequiredItems = UpgradeRequirements[UpgradeInfo.UpgradeLevel].RequiredItems;
    }

    return RequiredItems;
}
