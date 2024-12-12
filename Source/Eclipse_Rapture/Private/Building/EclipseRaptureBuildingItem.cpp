#include "Building/EclipseRaptureBuildingItem.h"
#include "Items/Item.h"
#include "Character/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"

AEclipseRaptureBuildingItem::AEclipseRaptureBuildingItem()
{
    PrimaryActorTick.bCanEverTick = false;
    BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Building Mesh"));
    RootComponent = BuildingMesh;
    CurrentUpgradeType = EUpgradeType::EUT_None; // Default upgrade type
    bShowDebugMessages = true;
}

void AEclipseRaptureBuildingItem::BeginPlay()
{
    Super::BeginPlay();
}

void AEclipseRaptureBuildingItem::UpgradeBuilding_Implementation(FUpgradeInfo UpgradeInfo, FUpgradeResults& Result)
{
    if (!UpgradeInfo.UpgraderInventory)
    {
        UE_LOG(LogTemp, Error, TEXT("Upgrade failed: Invalid inventory."));
        Result.bUpgradeSuccessful = false;
        Result.UpgradeResultMessage = FText::FromString("Upgrade failed: Invalid inventory.");
        return;
    }

    if (!UpgradeRequirements.Contains(UpgradeInfo.UpgradeType))
    {
        FString Message = FString::Printf(TEXT("Upgrade type %s is not valid for this building."), *UEnum::GetValueAsString(UpgradeInfo.UpgradeType));
        UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
        Result.bUpgradeSuccessful = false;
        Result.UpgradeResultMessage = FText::FromString(Message);
        return;
    }

    // Prevent upgrading to a lower tier
    if (UpgradeInfo.UpgradeType < CurrentUpgradeType)
    {
        FString Message = FString::Printf(TEXT("Cannot downgrade building from %s to %s."),
                                          *UEnum::GetValueAsString(CurrentUpgradeType),
                                          *UEnum::GetValueAsString(UpgradeInfo.UpgradeType));
        UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
        Result.bUpgradeSuccessful = false;
        Result.UpgradeResultMessage = FText::FromString(Message);
        return;
    }

    // Prevent upgrading to the same tier
    if (UpgradeInfo.UpgradeType == CurrentUpgradeType)
    {
        FString Message = FString::Printf(TEXT("Building is already upgraded to type %s."), *UEnum::GetValueAsString(UpgradeInfo.UpgradeType));
        UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
        Result.bUpgradeSuccessful = false;
        Result.UpgradeResultMessage = FText::FromString(Message);
        return;
    }

    FUpgradeRequirements Requirements = UpgradeRequirements[UpgradeInfo.UpgradeType];

    // Validate required items and quantities
    if (Requirements.RequiredItems.Num() != Requirements.RequiredQuantities.Num())
    {
        UE_LOG(LogTemp, Error, TEXT("Upgrade failed: Items and quantities mismatch for upgrade type %s."), *UEnum::GetValueAsString(UpgradeInfo.UpgradeType));
        Result.bUpgradeSuccessful = false;
        Result.UpgradeResultMessage = FText::FromString("Upgrade failed: Items and quantities mismatch.");
        return;
    }

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
            UE_LOG(LogTemp, Warning, TEXT("%s"), *MissingItemMessage);
            Result.bUpgradeSuccessful = false;
            Result.UpgradeResultMessage = FText::FromString(MissingItemMessage);
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
        UE_LOG(LogTemp, Log, TEXT("%s"), *RemovedItemMessage);
    }

    // Apply new material
    if (BuildingMesh && Materials.Contains(UpgradeInfo.UpgradeType))
    {
        BuildingMesh->SetMaterial(0, Materials[UpgradeInfo.UpgradeType]);
        FString UpgradeMessage = FString::Printf(TEXT("Building upgraded to type %s."), *UEnum::GetValueAsString(UpgradeInfo.UpgradeType));
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, UpgradeMessage);
        UE_LOG(LogTemp, Log, TEXT("%s"), *UpgradeMessage);
    }

    // Update the current upgrade type
    CurrentUpgradeType = UpgradeInfo.UpgradeType;
    Result.bUpgradeSuccessful = true;
    Result.UpgradeResultMessage = FText::FromString("Upgrade successful.");
}


TArray<TSubclassOf<AItem>> AEclipseRaptureBuildingItem::GetRequiredUpgradeItems_Implementation(FUpgradeInfo UpgradeInfo)
{
    TArray<TSubclassOf<AItem>> RequiredItems;

    if (UpgradeRequirements.Contains(UpgradeInfo.UpgradeType))
    {
        RequiredItems = UpgradeRequirements[UpgradeInfo.UpgradeType].RequiredItems;
    }

    return RequiredItems;
}

AEclipseRaptureBuildingItem* AEclipseRaptureBuildingItem::GetBuildingItem_Implementation()
{
    return this;
}

EBuildingType AEclipseRaptureBuildingItem::GetBuildingType_Implementation()
{
    return BuildingType;
}
