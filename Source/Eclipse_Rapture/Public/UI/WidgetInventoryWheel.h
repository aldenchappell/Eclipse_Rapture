// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetInventoryWheel.generated.h"

/**
 * 
 */
UCLASS()
class ECLIPSE_RAPTURE_API UWidgetInventoryWheel : public UUserWidget
{
	GENERATED_BODY()
	
public:

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (ExposeOnSpawn = "true"))
	TObjectPtr<class UInventoryComponent> InventoryComponent;

};
