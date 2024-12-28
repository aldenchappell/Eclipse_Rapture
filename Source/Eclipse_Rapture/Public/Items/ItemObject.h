// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Character/EclipseRaptureCharacter.h"
#include "Structures/FInventoryTypes.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemObject.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemCountIncrease);
UCLASS(Blueprintable)
class ECLIPSE_RAPTURE_API UItemObject : public UObject
{
	GENERATED_BODY()
	
public:
	UItemObject();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Item Properties")
	FOnItemCountIncrease OnItemCountIncrease;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Inventory Space", meta = (ExposeOnSpawn = "true"))
	TSubclassOf<class AItem> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Inventory Space", meta = (ExposeOnSpawn = "true"))
	FInventorySpaceRequirements InventorySpaceRequired;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	EUseImpactType UseImpactType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	EMainItemUseDescriptionType MainItemUseDescriptionType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	ESecondaryItemUseDescriptionType SecondaryItemUseDescriptionType;

#pragma region UI Implements
	//Text for using item(Equip, Consume, etc)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Properties")
	FText UseActionText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Properties")
	TObjectPtr<UStaticMesh> PickupMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties", meta = (ExposeOnSpawn = "true"))
	TObjectPtr<UMaterialInterface> ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties", meta = (ExposeOnSpawn = "true"))
	TObjectPtr<UMaterialInterface> ItemIconRotated;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Item Properties")
	void Rotate();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Properties")
	TObjectPtr<UTexture2D> ItemUseIcon;

	//Name to show inside of inventory
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Properties")
	FText ItemDisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Properties", meta = (MultiLine = true))
	FText ItemDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Properties", meta = (ClampMin = 0.0))
	float ItemWeight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Properties", meta = (ClampMin = 0.0))
	int32 MaxStackSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Pickup Properties")
	FText ItemInteractionPrompt;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Item Pickup Properties")
	int32 MinItemDropAmount;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Item Pickup Properties")
	int32 MaxItemDropAmount;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Item Pickup Properties")
	void InitializeItemAmount();

	//TODO: MOVE THESE VARIABLES TO PRIVATE!!
	//how many of this object is rewarded to the player/is in this stack of item(s)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 ItemAmount;

	//how many items are in this stack
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 ItemCount;
#pragma endregion

private:

	UPROPERTY()
	bool bRotated;

	

	
public:
	UFUNCTION(BlueprintPure, BlueprintCallable)
	int32 GetItemAmount() const { return ItemAmount; }

	UFUNCTION(BlueprintCallable)
	void SetItemAmount(int32 NewAmount);

	UFUNCTION(BlueprintPure, BlueprintCallable)
	int32 GetItemCount() const { return ItemCount; }

	UFUNCTION(BlueprintCallable)
	void SetItemCount(int32 NewCount);

	UFUNCTION(BlueprintPure, Blueprintcallable)
	FText GetItemDisplayName() const { return ItemDisplayName; }

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Blueprintcallable)
	FInventorySpaceRequirements GetInventorySpaceRequirements();

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, BlueprintCallable)
	class UMaterialInterface* GetItemIcon() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	bool GetIsRotated() const { return bRotated; }

	UFUNCTION(BlueprintCallable)
	void SetIsRotated(bool bNewIsRotated);

	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetItemWeight() const { return ItemWeight; }

	UFUNCTION(BlueprintPure, BlueprintCallable)
	int32 GetMaxStackSize() const { return MaxStackSize; }

	UFUNCTION(BlueprintPure, BlueprintCallable)
	FText GetItemDescription() const { return ItemDescription; }

	UFUNCTION(BlueprintPure, BlueprintCallable)
	FText GetUseActionText() const { return UseActionText; }

	UFUNCTION(BlueprintPure, BlueprintCallable)
	FText GetItemInteractionPrompt() const { return ItemInteractionPrompt; }

	UFUNCTION(BlueprintCallable, Category = "Item Properties")
	UTexture2D* GetItemUseIcon() const { return ItemUseIcon; }

	UFUNCTION(BlueprintCallable, Category = "Item Properties")
	EUseImpactType GetUseImpactType() const { return UseImpactType; }

	UFUNCTION(BlueprintCallable, Category = "Item Properties")
	EMainItemUseDescriptionType GetMainItemUseDescriptionType() const { return MainItemUseDescriptionType; }

	UFUNCTION(BlueprintCallable, Category = "Item Properties")
	ESecondaryItemUseDescriptionType GetSecondaryItemUseDescriptionType() const { return SecondaryItemUseDescriptionType; }

	UFUNCTION(BlueprintCallable, Category = "Item Properties")
	UStaticMesh* GetPickupMesh() const { return PickupMesh; }

	UFUNCTION(BlueprintCallable, Category = "Item Properties")
	TSubclassOf<AItem> GetItemClass() const { return ItemClass; }
};
