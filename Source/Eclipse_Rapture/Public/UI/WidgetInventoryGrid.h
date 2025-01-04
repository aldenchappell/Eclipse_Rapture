// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetInventoryGrid.generated.h"


class UBorder;
class UScrollBox;
class UWrapBox;
class UInventoryComponent;
UCLASS()
class ECLIPSE_RAPTURE_API UWidgetInventoryGrid : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Inventory Grid")
	void DisplayInventory(UInventoryComponent* Inventory);

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Item Data", meta = (ExposeOnSpawn = "true"))
	TObjectPtr<UInventoryComponent> InventoryComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "UI Elements", meta = (BindWidget))
	TObjectPtr<UBorder> GridBorder;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "UI Elements", meta = (BindWidget))
	TObjectPtr<UScrollBox> GridScrollBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "UI Elements", meta = (BindWidget))
	TObjectPtr<UWrapBox> GridWrapBox;
};
