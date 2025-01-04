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
	TArray<FInventorySlotData> InventoryItems;

    UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "New Inventory")
    int32 InventorySlots;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "New Inventory")
    void FindSlot(FName ItemID);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "New Inventory")
	bool AddToInventory(FName ItemID, int32 Quantity, int32& QuantityRemaining);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "New Inventory")
	bool RemoveFromInventory(FName ItemID, int32 Quantity, int32& QuantityRemaining);

    UFUNCTION(BlueprintNativeEvent, BlueprintPure, BlueprintCallable, Category = "New Inventory")
	int32 GetMaxStackSize(FName ItemID);

    UFUNCTION(BlueprintNativeEvent, BlueprintPure, BlueprintCallable, Category = "New Inventory")
	bool FindInventorySlot(FName ItemID, int32& SlotIndex);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "New Inventory")
    void AddToExistingStack(int32 Index, int32 Quantity);

    UFUNCTION(BlueprintNativeEvent, BlueprintPure, BlueprintCallable, Category = "New Inventory")
	bool IsEmptySlotAvailable(int32& EmptyIndex);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "New Inventory")
	bool CreateNewStack(FName ItemID, int32 Quantity);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "New Inventory")
	void TransferSlots(int32 SourceIndex, UInventoryComponent* SourceInventory, int32 DestinationIndex);

#pragma endregion

    // Delegate for inventory updates
    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Inventory | Inventory Delegates")
    FOnInventoryUpdated OnInventoryUpdated;
};
