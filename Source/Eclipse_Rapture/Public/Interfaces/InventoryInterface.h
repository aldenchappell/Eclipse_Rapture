// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Structures/FInventoryTypes.h"
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InventoryInterface.generated.h"


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInventoryInterface : public UInterface
{
	GENERATED_BODY()
};

class AItem;
class UItemObject;
/**
 * 
 */
class ECLIPSE_RAPTURE_API IInventoryInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "New Inventory")
	TArray<FInventorySlotData> GetAllItems();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "New Inventory")
	void GetAmountOfItem(FInventorySlotData Data, int32& Amount);
};
