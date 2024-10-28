// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "FoodItem.generated.h"

/**
 * 
 */
UCLASS()
class ECLIPSE_RAPTURE_API AFoodItem : public AItem
{
	GENERATED_BODY()
	
public:
	virtual void Interact_Implementation(AEclipseRaptureCharacter* Character) override;
	AFoodItem();

protected:
	virtual void Use(class AEclipseRaptureCharacter* Character) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Healing")
	float FoodSatietyHealAmount = 25.0f;
};
