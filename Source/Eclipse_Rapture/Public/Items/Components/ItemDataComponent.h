// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemDataComponent.generated.h"

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ECLIPSE_RAPTURE_API UItemDataComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UItemDataComponent();

protected:
	
	virtual void BeginPlay() override;

	//Item ID Data Table Value
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Item Properties | Data")
	FDataTableRowHandle ItemID;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties | Data")
	int32 ItemQuantity;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Item Pickup Properties")
	int32 MinItemPickupQuantity;
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Item Pickup Properties")
	int32 MaxItemPickupQuantity;
};
