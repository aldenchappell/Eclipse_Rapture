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
};