// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Structures/FStorageItem.h"
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveData_Level.generated.h"

/**
 * 
 */
UCLASS()
class ECLIPSE_RAPTURE_API USaveData_Level : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Saved Data")
	TArray<TSoftObjectPtr<AActor>> ActorsRemoved;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Saved Data")
	TMap<TSoftClassPtr<AActor>, FTransform> ActorsAdded;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Saved Data")
	TMap <TSoftObjectPtr<class UInventoryComponent> , FStorageItemStruct> StorageItemsAdded;
};
