// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

//Blueprints will bind to this to update UI on inventory change
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

//forward declarations
class AItem;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ECLIPSE_RAPTURE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	virtual void BeginPlay() override;

	bool AddItem(AItem* ItemToAdd);
	bool RemoveItem(AItem* ItemToRemove);

	//items player starts with
	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<TObjectPtr<AItem>> DefaultItems;

	//how many items can the player carry?
	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Inventory | Inventory Properties")
	int32 Capacity;

	//delegate for inventory update
	UPROPERTY(BlueprintAssignable, Category = "Inventory | Inventory Delegates")
	FOnInventoryUpdated OnInventoryUpdated;

	//number of items in inventory currently
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory | Inventory Properties")
	TArray<TObjectPtr<AItem>> Items;
		
};
