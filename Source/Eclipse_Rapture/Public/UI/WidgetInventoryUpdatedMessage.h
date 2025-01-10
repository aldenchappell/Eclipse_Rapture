// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Structures/FInventoryTypes.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetInventoryUpdatedMessage.generated.h"

/**
 * 
 */
UCLASS()
class ECLIPSE_RAPTURE_API UWidgetInventoryUpdatedMessage : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Properties", meta = (ExposeOnSpawn = "true"))
	FText DisplayName;

	//This is the operator that will be displayed in the message - Example + or - for adding or removing items
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Properties", meta = (ExposeOnSpawn = "true"))
	FText DisplayOperator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Properties", meta = (ExposeOnSpawn = "true"))
	int32 Quantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Properties")
	EInventoryUpdateTypes LastUpdateType;
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI Elements", meta = (BindWidget))
	class UTextBlock* UpdateMessageText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI Elements", meta = (BindWidget))
	class UBorder* UpdateBorder;

	
};
