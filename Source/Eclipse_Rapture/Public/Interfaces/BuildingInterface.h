// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BuildingInterface.generated.h"

USTRUCT(BlueprintType)
struct FUpgradeInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Building | Upgrade")
	class UInventoryComponent* UpgraderInventory;

	/*UPROPERTY()
	class */
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
};
