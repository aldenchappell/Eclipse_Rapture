// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Structures/FInventoryTypes.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetItem.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRemoved, class AItem*, Item);
UCLASS()
class ECLIPSE_RAPTURE_API UWidgetItem : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class USizeBox> BackgroundSizeBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UImage> ItemImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> ItemCountText;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Private")
	FOnRemoved OnRemoved;

	UPROPERTY(BlueprintReadWrite, Category = "Item Data")
	FItemData ItemData;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Private | Design", meta = (ExposeOnSpawn = "true"))
	float TileSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Private | Design")
	FVector2D Size;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Private", meta = (ExposeOnSpawn = "true"))
	TObjectPtr<class AItem> Item;

	UPROPERTY(BlueprintReadWrite, Category = "Private", meta = (ExposeOnSpawn = "true"))
	int32 ItemCount;

public:

	UFUNCTION(BlueprintCallable)
	void SetItem(class AItem* NewItem);
};
