#include "Building/EclipseRaptureBuildingItem.h"
#include "Items/Item.h"
#include "Character/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Items/ItemObject.h"

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
#pragma region Function Pre-Conditions
    // Ensure Upgrade Inventory is valid
    if (!UpgradeInfo.UpgraderInventory)
    {
        //UE_LOG(LogTemp, Error, TEXT("Upgrade failed: Invalid inventory."));
        Result.bUpgradeSuccessful = false;
        Result.UpgradeResultMessage = FText::FromString("Upgrade failed: Invalid inventory.");
        return;
    }

    // Get DisplayName for enums
    const UEnum* UpgradeTypeEnum = StaticEnum<EUpgradeType>();
    const UEnum* BuildingTypeEnum = StaticEnum<EBuildingType>();

    FString UpgradeTypeDisplayName = UpgradeTypeEnum->GetDisplayNameTextByValue(static_cast<int64>(UpgradeInfo.UpgradeType)).ToString();
    FString CurrentUpgradeTypeDisplayName = UpgradeTypeEnum->GetDisplayNameTextByValue(static_cast<int64>(CurrentUpgradeType)).ToString();
    FString BuildingTypeDisplayName = BuildingTypeEnum->GetDisplayNameTextByValue(static_cast<int64>(BuildingType)).ToString();

	if (bDisableInteractionOnMaxUpgrade && CurrentUpgradeType == EUpgradeType::EUT_Reinforced)
	{
		FString Message = FString::Printf(TEXT("Building is already at max upgrade level %s."), *UpgradeTypeDisplayName);
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
		Result.bUpgradeSuccessful = false;
		Result.UpgradeResultMessage = FText::FromString(Message);
		return;
	}

    // Check if upgrade type is valid
    if (!UpgradeRequirements.Contains(UpgradeInfo.UpgradeType))
    {
        FString Message = FString::Printf(TEXT("Upgrade type %s is not valid for this %s."), *UpgradeTypeDisplayName, *BuildingTypeDisplayName);
       // UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
        Result.bUpgradeSuccessful = false;
        Result.UpgradeResultMessage = FText::FromString(Message);
        return;
    }

    // Prevent downgrading
    if (UpgradeInfo.UpgradeType < CurrentUpgradeType)
    {
        FString Message = FString::Printf(TEXT("Cannot downgrade building from %s to %s."), *CurrentUpgradeTypeDisplayName, *UpgradeTypeDisplayName);
        //UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
        Result.bUpgradeSuccessful = false;
        Result.UpgradeResultMessage = FText::FromString(Message);
        return;
    }

    // Prevent upgrading to the same type
    if (UpgradeInfo.UpgradeType == CurrentUpgradeType)
    {
        FString Message = FString::Printf(TEXT("Building is already upgraded to type %s."), *UpgradeTypeDisplayName);
        //UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
        Result.bUpgradeSuccessful = false;
        Result.UpgradeResultMessage = FText::FromString(Message);
        return;
    }
#pragma endregion

    //Get upgrade requirements for the desired upgrade type
    FUpgradeRequirements Requirements = UpgradeRequirements[UpgradeInfo.UpgradeType];

    ValidateRequiredItems(Requirements, UpgradeTypeDisplayName, Result);

    CheckInventory(Requirements, UpgradeInfo, Result);

    DeductInventoryItems(Requirements, UpgradeInfo);

    ApplyUpgradedMaterial(UpgradeInfo, UpgradeTypeDisplayName, Result);

    // Update the current upgrade type
    CurrentUpgradeType = UpgradeInfo.UpgradeType;
    Result.bUpgradeSuccessful = true;
}

void AEclipseRaptureBuildingItem::ValidateRequiredItems(FUpgradeRequirements& Requirements, FString& UpgradeTypeDisplayName, FUpgradeResults& Result)
{
    // Validate required items and quantities
    if (Requirements.RequiredItems.Num() != Requirements.RequiredQuantities.Num())
    {
        FString Message = FString::Printf(TEXT("Upgrade failed: Mismatch between required items and quantities for upgrade type %s."), *UpgradeTypeDisplayName);
        //UE_LOG(LogTemp, Error, TEXT("%s"), *Message);
        Result.bUpgradeSuccessful = false;
        Result.UpgradeResultMessage = FText::FromString(Message);
        return;
    }
}

void AEclipseRaptureBuildingItem::DeductInventoryItems(FUpgradeRequirements& Requirements, FUpgradeInfo& UpgradeInfo)
{
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
        //UE_LOG(LogTemp, Log, TEXT("%s"), *RemovedItemMessage);
    }
}

void AEclipseRaptureBuildingItem::ApplyUpgradedMaterial(FUpgradeInfo& UpgradeInfo, FString& UpgradeTypeDisplayName, FUpgradeResults& Result)
{
    // Apply the new material for the upgraded type
    if (BuildingMesh && Materials.Contains(UpgradeInfo.UpgradeType))
    {
        BuildingMesh->SetMaterial(0, Materials[UpgradeInfo.UpgradeType]);
        FString UpgradeMessage = FString::Printf(TEXT("Building upgraded to type %s."), *UpgradeTypeDisplayName);
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, UpgradeMessage);
        //UE_LOG(LogTemp, Log, TEXT("%s"), *UpgradeMessage);
        Result.UpgradeResultMessage = FText::FromString(UpgradeMessage);
    }
    else
    {
        FString MaterialFailMessage = FString::Printf(TEXT("Upgrade succeeded, but no material found for type %s."), *UpgradeTypeDisplayName);
        //UE_LOG(LogTemp, Warning, TEXT("%s"), *MaterialFailMessage);
        Result.UpgradeResultMessage = FText::FromString(MaterialFailMessage);
    }
}

void AEclipseRaptureBuildingItem::CheckInventory(FUpgradeRequirements& Requirements, FUpgradeInfo& UpgradeInfo, FUpgradeResults& Result)
{
    // Check if the inventory contains enough of the required items
    for (int32 Index = 0; Index < Requirements.RequiredItems.Num(); ++Index)
    {
        TSubclassOf<AItem> ItemClass = Requirements.RequiredItems[Index];
        int32 RequiredQuantity = Requirements.RequiredQuantities[Index];

        // Check if the inventory contains enough of the required item
        if (!UpgradeInfo.UpgraderInventory->CheckForItem(ItemClass) ||
            UpgradeInfo.UpgraderInventory->GetItemAmount(ItemClass) < RequiredQuantity)
        {
            // Get the item display name
            FString ItemDisplayName = "Unknown Item";
            if (ItemClass)
            {
                // Create a default instance of the item to access its display name
                AItem* Item = Cast<AItem>(ItemClass->GetDefaultObject());
                if (Item)
                {
                    ItemDisplayName = Item->GetItemObject()->GetItemDisplayName().ToString();
                }
            }

            // Create the error message
            FString MissingItemMessage = FString::Printf(
                TEXT("Missing %d of item: %s"),
                RequiredQuantity,
                *ItemDisplayName
            );

            // Log and update the result
            UE_LOG(LogTemp, Warning, TEXT("%s"), *MissingItemMessage);
            Result.bUpgradeSuccessful = false;
            Result.UpgradeResultMessage = FText::FromString(MissingItemMessage);
            return;
        }
    }
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

void AEclipseRaptureBuildingItem::TakeDamage_Implementation(FDamageInfo DamageInfo)
{

}

void AEclipseRaptureBuildingItem::DropItems_Implementation(const TArray<TSubclassOf<class AItem>>& InventoryItems)
{

}

float AEclipseRaptureBuildingItem::GetMaxHealth_Implementation()
{
    return 0.0f;
}

float AEclipseRaptureBuildingItem::GetCurrentHealth_Implementation()
{
    return 0.0f;
}

float AEclipseRaptureBuildingItem::GetCriticalHealthThreshold_Implementation()
{
    return 0.0f;
}

bool AEclipseRaptureBuildingItem::GetIsDead_Implementation()
{
    return false;
}
