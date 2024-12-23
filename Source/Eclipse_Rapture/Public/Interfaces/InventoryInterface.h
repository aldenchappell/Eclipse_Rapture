// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Delegates/Delegate.h"
#include "Structures/FInventoryTypes.h"
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InventoryInterface.generated.h"


DECLARE_DYNAMIC_DELEGATE(FOnForEachIndexCompleted);
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

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Inventory | Adding")
	bool TryAddItem(UItemObject* ItemObject);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Inventory | Adding")
	bool IsRoomAvailable(UItemObject* ItemObject, int32 TopLeftTileIndex);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "New Inventory")
	bool TryRemoveItem(UItemObject* ItemObject);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "New Inventory")
	void IndexToTile(int32 Index, FInventorySpaceRequirements& Requirements);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "New Inventory")
	bool IsTileValid(FInventorySpaceRequirements Tiling);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "New Inventory")
	bool GetItemAtIndex(int32 Index, UItemObject*& Item);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "New Inventory")
	int32 TileToIndex(FInventorySpaceRequirements Tiling);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "New Inventory")
	void AddItemAt(UItemObject* ItemObject, int32 TopLeftIndex);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Inventory")
	void ForEachIndex(UItemObject* ItemObject, int32 TopLeftInventoryIndex, FInventorySpaceRequirements& Requirements, const FSimpleDelegate& OnCompleted);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Inventory")
	void GetAllItems(TMap<UItemObject*, FInventorySpaceRequirements>& AllItems);
};
