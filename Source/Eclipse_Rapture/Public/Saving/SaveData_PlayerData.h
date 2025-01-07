// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Structures/FInventoryTypes.h"
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveData_PlayerData.generated.h"

/**
 * 
 */
UCLASS()
class ECLIPSE_RAPTURE_API USaveData_PlayerData : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "New Inventory")
	TArray<FInventorySlotData> InventoryItems;
protected:

};
