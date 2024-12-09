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

	UPROPERTY(BlueprintReadonly, Category = "Building | Upgrade")
	class AEclipseRaptureBuildingItem* BuildingItem;

	//Upgrade level (0 = Wood, 1 = Brick, 2 = Metal, 3 = Reinforced) 
	UPROPERTY(BlueprintReadonly, Category = "Building | Upgrade")
	int32 UpgradeLevel;

	UPROPERTY(BlueprintReadonly, Category = "Building | Upgrade")
	EUpgradeCostType UpgradeCostType;
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
	void UpgradeBuilding(FUpgradeInfo UpgradeInfo);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Building | Interfaces")
	class AEclipseRaptureBuildingItem* GetBuildingItem();
};
