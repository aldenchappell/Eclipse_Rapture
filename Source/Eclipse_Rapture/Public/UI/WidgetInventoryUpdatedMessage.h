// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Properties")
	FText DisplayName;

	//This is the operator that will be displayed in the message - Example + or - for adding or removing items
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Properties")
	FText DisplayOperator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Properties")
	int32 Quantity;
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI Elements", meta = (BindWidget))
	class UTextBlock* UpdateMessageText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI Elements", meta = (BindWidget))
	class UBorder* UpdateBorder;

	
};
