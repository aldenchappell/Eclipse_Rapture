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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnItemAdded, FName, ItemID, int32, QuantityAdded, EInventoryUpdateTypes, UpdateType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnItemRemoved, FName, ItemID, int32, QuantityRemoved, EInventoryUpdateTypes, UpdateType);

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ECLIPSE_RAPTURE_API UInventoryComponent : public UActorComponent, public IInventoryInterface
{
    GENERATED_BODY()

public:
    UInventoryComponent();
    virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(BlueprintReadWrite, Category = "New Inventory")
    TObjectPtr<class AEclipseRaptureCharacter> OwningCharacter;

#pragma region New Inventory Functions and Variables

    // Items the player starts with, including specified quantities
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
    TArray<FInventorySlotData> DefaultItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "New Inventory")
	TArray<FInventorySlotData> InventoryItems;

    UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "New Inventory")
    int32 InventorySlots;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "New Inventory")
    void FindSlot(FName ItemID);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "New Inventory")
	bool AddToInventory(FName ItemID, int32 Quantity, int32& QuantityRemaining);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "New Inventory")
	bool RemoveFromInventory(int32 Index, bool RemoveWholeStack, bool IsConsumed);

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

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "New Inventory")
	void DropItem(FName ItemID, int32 Quantity);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "New Inventory")
    bool UseItem(int32 Index);

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, BlueprintCallable, Category = "New Inventory")
    FItemData GetItemData(FName ItemID);

    UFUNCTION(BlueprintNativeEvent, BlueprintPure, BlueprintCallable, Category = "New Inventory")
	FVector GetDropLocation();

    UFUNCTION(BlueprintNativeEvent, BlueprintPure, BlueprintCallable, Category = "New Inventory")
	bool QueryInventory(FName ItemID, int32 Quantity, int32& FoundQuantity, int32& IndexFound);

    UFUNCTION(BlueprintNativeEvent, BlueprintPure, BlueprintCallable, Category = "New Inventory")
    int32 GetQuantityOfItem();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "New Inventory")
    void SaveInventory();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "New Inventory")
    void LoadInventory();

#pragma endregion

#pragma region Inventory Delegates
    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Inventory | Inventory Delegates")
    FOnInventoryUpdated OnInventoryUpdated;

    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Inventory | Inventory Delegates")
    FOnItemAdded OnItemAdded;

    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Inventory | Inventory Delegates")
    FOnItemRemoved OnItemRemoved;

#pragma endregion
};
