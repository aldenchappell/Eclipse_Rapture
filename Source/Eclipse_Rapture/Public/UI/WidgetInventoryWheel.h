// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetInventoryWheel.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuickAccessWheelOpen);

UCLASS()
class ECLIPSE_RAPTURE_API UWidgetInventoryWheel : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Wheel | Events")
	FOnQuickAccessWheelOpen OnQuickAccessWheelOpen;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Wheel | Components", meta = (ExposeOnSpawn = "true"))
	TObjectPtr<class UInventoryComponent> InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Wheel | Widget Bindings", meta = (BindWidget))
	TObjectPtr<class UImage> QuickAccessWheel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Wheel | Properties")
	int32 WheelSectionCount = 4;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Wheel | Properties")
	int32 WheelSectionSize;
};
