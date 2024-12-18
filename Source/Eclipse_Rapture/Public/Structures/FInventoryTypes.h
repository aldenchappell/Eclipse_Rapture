#pragma once

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

    // Default constructor
    FInventorySpaceRequirements()
        : RowsRequired(0), ColumnsRequired(0)
    {
    }

    // Custom constructor to initialize rows and columns
    FInventorySpaceRequirements(int32 InRowsRequired, int32 InColumnsRequired)
        : RowsRequired(InRowsRequired), ColumnsRequired(InColumnsRequired)
    {
    }
};


USTRUCT(BlueprintType)
struct FInventoryTile
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Tile")
    FVector2D XTiling;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Tile")
    FVector2D YTiling;

    FInventoryTile() : XTiling(0,0), YTiling(0,0) {}

	FInventoryTile(FVector2D InXTiling, FVector2D InYTiling) : XTiling(InXTiling), YTiling(InYTiling) {}
};
