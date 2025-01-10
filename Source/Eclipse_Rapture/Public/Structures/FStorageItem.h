#pragma once

#include "FInventoryTypes.h"
#include "CoreMinimal.h"
#include "FStorageItem.generated.h"

USTRUCT(BlueprintType)
struct FStorageItemStruct
{
    GENERATED_BODY()
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Storage Container Item")
    TArray<FInventorySlotData> SlotData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Storage Container Item")
    FTransform StorageItemTransform;
};