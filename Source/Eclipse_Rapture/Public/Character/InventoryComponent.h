#pragma once

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

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ECLIPSE_RAPTURE_API UInventoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UInventoryComponent();
    virtual void BeginPlay() override;

    


#pragma region New Inventory Functions and Variables

    UFUNCTION(BlueprintCallable, Category = "New Inventory")
    bool TryAddItem(AItem* Item);

    UFUNCTION(BlueprintCallable, Category = "New Inventory")
	bool IsRoomAvailable(AItem* Item, int32 TopLeftTileIndex);

    UFUNCTION(BlueprintCallable, Category = "New Inventory")
    FInventorySpaceRequirements IndexToTile(int32 Index);

    UFUNCTION(BlueprintCallable, Category = "New Inventory")
    bool IsTileValid(FInventorySpaceRequirements Tiling);

    UFUNCTION(BlueprintCallable, Category = "New Inventory")
	bool GetItemAtIndex(int32 Index, AItem*& Item);

    UFUNCTION(BlueprintCallable, Category = "New Inventory")
    int32 TileToIndex(FInventorySpaceRequirements Tiling);

	UFUNCTION(BlueprintCallable, Category = "New Inventory")
	void AddItemAt(AItem* Item, int32 TopLeftIndex);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    FInventorySpaceRequirements ForEachIndex(AItem* Item, int32 TopLeftInventoryIndex);


	UPROPERTY(BlueprintReadWrite, Category = "New Inventory")
    bool bIsDirty = false;

	UPROPERTY(BlueprintReadWrite, Category = "New Inventory")
	TArray<AItem*> InventoryItems;

    UPROPERTY(EditAnywhere,BlueprintReadonly, Category = "New Inventory")
    int32 Rows = 6;

    UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "New Inventory")
    int32 Columns = 15;

#pragma endregion

    // Add a single item
    UFUNCTION(BlueprintCallable)
    bool AddItem(TSubclassOf<AItem> ItemClass);

    // Add a specified amount of an item
    UFUNCTION(BlueprintCallable)
    bool AddItemAmount(TSubclassOf<AItem> ItemClass, int32 Amount);

    // Remove a single item
    UFUNCTION(BlueprintCallable)
    bool RemoveItem(TSubclassOf<AItem> ItemClass);

    // Remove multiple items
    UFUNCTION(BlueprintCallable)
    bool RemoveItemAmount(TSubclassOf<AItem> ItemClass, int32 Amount);

    // Items the player starts with, including specified quantities
    UPROPERTY(EditDefaultsOnly, Category = "Inventory")
    TArray<FDefaultItem> DefaultItems;

    // Inventory capacity (maximum number of item types)
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory | Inventory Properties")
    int32 Capacity;

    // Delegate for inventory updates
    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Inventory | Inventory Delegates")
    FOnInventoryUpdated OnInventoryUpdated;

    // Map of item types and their quantities
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory | Inventory Properties")
    TMap<TSubclassOf<AItem>, int32> Items;

    // Array to store actual item instances
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory | Inventory Properties")
    TArray<AItem*> ItemInstances;

    // Check if the player has at least one of the specified item
    UFUNCTION(BlueprintPure)
    bool CheckForItem(TSubclassOf<AItem> ItemClass);

    // Get the quantity of a specific item type in the inventory
    UFUNCTION(BlueprintPure)
    int32 GetItemAmount(TSubclassOf<AItem> ItemClass);

    // Get an instance of a specific item type
    UFUNCTION(BlueprintPure)
    AItem* GetItemInstance(TSubclassOf<AItem> ItemClass);

private:
    // Helper function to get max stack size of an item type
    int32 GetMaxStackSize(TSubclassOf<AItem> ItemClass) const;

    UFUNCTION()
    void PopulateDefaultItems();
};
