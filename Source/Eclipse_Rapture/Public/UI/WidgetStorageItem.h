// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetStorageItem.generated.h"

/**
 * 
 */
UCLASS()
class ECLIPSE_RAPTURE_API UWidgetStorageItem : public UUserWidget
{
	GENERATED_BODY()
	
public:

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> StorageCanvas;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, meta = (BindWidget))
	TObjectPtr<class UWidgetInventoryGrid> PlayerInventoryGrid;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, meta = (BindWidget))
	TObjectPtr<class UWidgetInventoryGrid> StorageItemInventoryGrid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Data", meta = (ExposeOnSpawn = "true"))
	TObjectPtr<class UInventoryComponent> StorageItemInventoryComponent;
};
