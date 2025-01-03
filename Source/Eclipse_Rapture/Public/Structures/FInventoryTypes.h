#pragma once

#include "Items/ItemTypes.h"
#include "CoreMinimal.h"
#include "FInventoryTypes.generated.h"

USTRUCT(BlueprintType)
struct FInventorySlotData
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Display Properties")
    FName ItemID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Display Properties")
	int32 Quantity;
};

USTRUCT(BlueprintType)
struct FItemData: public FTableRowBase
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
	TSubclassOf<class AItem> ItemClass;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
    EItemType ItemType;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
    EUsecaseType UsecaseType;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
    bool bDestroyOnPickup;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
    EUseImpactType UseImpactType;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
    EMainItemUseDescriptionType MainItemUseDescriptionType;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
    ESecondaryItemUseDescriptionType SecondaryItemUseDescriptionType;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
    FText UseActionText;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
    UTexture2D* ItemIcon;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data")
    UTexture2D* ItemIconRotated;
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
