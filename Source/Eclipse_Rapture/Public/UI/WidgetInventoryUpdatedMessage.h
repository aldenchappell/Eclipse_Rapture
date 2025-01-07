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
	FText UpdateMessage;
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI Elements", meta = (BindWidget))
	class UTextBlock* UpdateMessageText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI Elements", meta = (BindWidget))
	class UBorder* UpdateBorder;

	
};
