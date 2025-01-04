#pragma once

#include "Interfaces/InventoryInterface.h"
#include "Structures/FInventoryTypes.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

// Forward declaration
class AItem;

// Blueprint multicast delegate to notify UI updates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

USTRUCT(BlueprintType)
struct FDefaultItem
{
    GENERATED_BODY()

    // The item class
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    TSubclassOf<AItem> Item;

    // The quantity of the item
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    int32 Quantity;

    FDefaultItem()
        : Item(nullptr), Quantity(1)
    {
    }  // Default quantity is 1
};

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ECLIPSE_RAPTURE_API UInventoryComponent : public UActorComponent, public IInventoryInterface
{
    GENERATED_BODY()

public:
    UInventoryComponent();
    virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

#pragma region New Inventory Functions and Variables

    // Items the player starts with, including specified quantities
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
    TArray<FDefaultItem> DefaultItems;

	UPROPERTY(BlueprintReadWrite, Category = "New Inventory")
    bool bIsDirty = false;

	UPROPERTY(BlueprintReadWrite, Category = "New Inventory")
	TArray<AItem*> InventoryItems;

    UPROPERTY(BlueprintReadWrite, Category = "Inventory")
    TMap<TSubclassOf<AItem>, int32> ItemCounts;


#pragma region New Inventory Functions

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "New Inventory")
    bool TryAddItem(AItem* Item);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "New Inventory")
    bool IsRoomAvailable(AItem* Item, int32 TopLeftTileIndex);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "New Inventory")
    bool TryRemoveItem(AItem* Item);

    UFUNCTION(BlueprintNativeEvent, BlueprintPure, BlueprintCallable, Category = "New Inventory")
    void IndexToTile(int32 Index, FInventorySpaceRequirements& Requirements);

    UFUNCTION(BlueprintNativeEvent, BlueprintPure, BlueprintCallable, Category = "New Inventory")
    bool IsTileValid(FInventorySpaceRequirements Tiling);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "New Inventory")
    bool GetItemAtIndex(int32 Index, AItem*& Item);

    UFUNCTION(BlueprintNativeEvent, BlueprintPure, BlueprintCallable, Category = "New Inventory")
    int32 TileToIndex(FInventorySpaceRequirements Tiling);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "New Inventory")
    void AddItemAt(AItem* Item, int32 TopLeftIndex);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "New Inventory")
    void ForEachIndex(AItem* Item, int32 TopLeftInventoryIndex, FInventorySpaceRequirements& Requirements);

    UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "New Inventory")
    int32 Rows = 6;

    UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "New Inventory")
    int32 Columns = 15;
   
#pragma endregion

    // Delegate for inventory updates
    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Inventory | Inventory Delegates")
    FOnInventoryUpdated OnInventoryUpdated;

    UFUNCTION(BlueprintPure, BlueprintCallable)
	int32 GetTotalInventorySlots() const { return Rows * Columns; }

    // Helper function to get max stack size of an item type
    int32 GetMaxStackSize(TSubclassOf<AItem> ItemClass) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, BlueprintCallable)
	int32 FindTotalAmountOfItem(TSubclassOf<AItem> ItemClass, bool& ItemFound) const;

    UFUNCTION(BlueprintPure, BlueprintCallable)
	bool IsItemInInventory(TSubclassOf<AItem> ItemClass) const;
    
};
