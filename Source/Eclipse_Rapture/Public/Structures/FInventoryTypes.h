#pragma once

#include "Items/ItemTypes.h"
#include "CoreMinimal.h"
#include "FInventoryTypes.generated.h"



USTRUCT(BlueprintType)
struct FInventorySpaceRequirements
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Space")
    int32 RowsRequired;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Space")
    int32 ColumnsRequired;
};


USTRUCT(BlueprintType)
struct FInventoryTile
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Tile")
    FVector2D XTiling;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Tile")
    FVector2D YTiling;
};

USTRUCT(BlueprintType)
struct FItemData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
    EItemType ItemType;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
    EUsecaseType UsecaseType;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
    bool bDestroyOnPickup;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
    FInventorySpaceRequirements InventorySpaceRequired;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
    EUseImpactType UseImpactType;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
    EMainItemUseDescriptionType MainItemUseDescriptionType;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
    ESecondaryItemUseDescriptionType SecondaryItemUseDescriptionType;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
    FText UseActionText;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
    UMaterialInterface* ItemIcon;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
    UMaterialInterface* ItemIconRotated;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
    FText ItemDisplayName;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
    FText ItemDescription;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
    float ItemWeight;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
    int32 MaxStackSize;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
    FText ItemInteractionPrompt;
};
