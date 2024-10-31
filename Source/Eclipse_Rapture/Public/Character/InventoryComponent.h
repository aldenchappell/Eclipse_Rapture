// InventoryComponent.h

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

// Forward declarations
class AItem;

// Blueprint multicast delegate to notify UI updates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ECLIPSE_RAPTURE_API UInventoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UInventoryComponent();
    virtual void BeginPlay() override;

	//Item ID will help us keep track of all items in the game.
    //Will make it easier to check for items in the inventory
    UPROPERTY()
	int32 ItemID = 0;

    UFUNCTION(Blueprintcallable)
    bool AddItem(AItem* ItemToAdd);

    UFUNCTION(Blueprintcallable)
    bool RemoveItem(AItem* ItemToRemove);

    //Items the player starts with (Blueprint-assignable)
    UPROPERTY(EditDefaultsOnly, Category = "Inventory")
    TArray<TSubclassOf<AItem>> DefaultItems;

    // Inventory capacity
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory | Inventory Properties")
    int32 Capacity;

    // Delegate for inventory updates
    UPROPERTY(BlueprintAssignable, Category = "Inventory | Inventory Delegates")
    FOnInventoryUpdated OnInventoryUpdated;

    //Current items in the inventory
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory | Inventory Properties")
    TArray<AItem*> Items; 

    //Check if the player has at least one of the specified item
    UFUNCTION(BlueprintPure)
    bool CheckForItem(TSubclassOf<AItem> ItemClass);

    //Check how many items of a specific type the player has
    UFUNCTION(BlueprintPure)
    int32 GetItemAmount(TSubclassOf<AItem> ItemClass);

    //Get Item ID
    UFUNCTION(BlueprintCallable)
	int32 GetItemID() const { return ItemID; }
};