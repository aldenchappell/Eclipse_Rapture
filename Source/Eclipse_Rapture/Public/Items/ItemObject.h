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

UCLASS(Blueprintable)
class ECLIPSE_RAPTURE_API UItemObject : public UObject
{
	GENERATED_BODY()
	
public:
	UItemObject();

	UPROPERTY(BlueprintReadWrite, Category = "Item Properties")
	class AItem* OwningItem;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Inventory Space", meta = (ExposeOnSpawn = "true"))
	TSubclassOf<class AItem> ItemClass;

	

private:

	

	

	
public:

	
};
