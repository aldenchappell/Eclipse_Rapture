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
