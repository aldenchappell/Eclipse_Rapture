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


/**
 * 
 */
class ECLIPSE_RAPTURE_API IInventoryInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Inventory | Adding")
	bool TryAddItem(class AItem* Item);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Inventory | Adding")
	bool IsRoomAvailable(class AItem* Item, int32 TopLeftTileIndex);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "New Inventory")
	bool TryRemoveItem(class AItem* Item);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "New Inventory")
	void IndexToTile(int32 Index, FInventorySpaceRequirements& Requirements);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "New Inventory")
	bool IsTileValid(FInventorySpaceRequirements Tiling);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "New Inventory")
	bool GetItemAtIndex(int32 Index, class AItem*& Item);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "New Inventory")
	int32 TileToIndex(FInventorySpaceRequirements Tiling);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "New Inventory")
	void AddItemAt(class AItem* Item, int32 TopLeftIndex);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Inventory")
	void ForEachIndex(class AItem* Item, int32 TopLeftInventoryIndex, FInventorySpaceRequirements& Requirements);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Inventory")
	void GetAllItems(TMap<AItem*, FInventorySpaceRequirements>& AllItems);
};
