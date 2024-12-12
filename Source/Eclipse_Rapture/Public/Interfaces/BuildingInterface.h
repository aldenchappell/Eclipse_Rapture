// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Building/BuildingTypes.h"
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BuildingInterface.generated.h"

USTRUCT(BlueprintType)
struct FUpgradeInfo
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Building | Upgrade")
    class UInventoryComponent* UpgraderInventory;

    UPROPERTY(BlueprintReadWrite, Category = "Building | Upgrade")
    class AEclipseRaptureBuildingItem* BuildingItem;

    // The upgrade type requested (e.g., Wood, Metal, etc.)
    UPROPERTY(BlueprintReadWrite, Category = "Building | Upgrade")
    EUpgradeType UpgradeType;

    // List of required items for this upgrade
    UPROPERTY(BlueprintReadWrite, Category = "Building | Upgrade")
    TArray<TSubclassOf<class AItem>> RequiredItems;

    UPROPERTY(BlueprintReadWrite, Category = "Building | Upgrade")
    TArray<int32> RequiredQuantities;
};


USTRUCT(BlueprintType)
struct FUpgradeResults
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrade")
    bool bUpgradeSuccessful;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrade")
    FText UpgradeResultMessage;
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBuildingInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ECLIPSE_RAPTURE_API IBuildingInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Building | Interfaces")
	void UpgradeBuilding(FUpgradeInfo UpgradeInfo, FUpgradeResults& Result);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Building | Interfaces")
    TArray<TSubclassOf<AItem>> GetRequiredUpgradeItems(FUpgradeInfo UpgradeInfo);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Building | Interfaces")
	class AEclipseRaptureBuildingItem* GetBuildingItem();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Building | Interfaces")
    EBuildingType GetBuildingType();
};
