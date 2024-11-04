// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "HealthItem.generated.h"

/**
 * 
 */
UCLASS()
class ECLIPSE_RAPTURE_API AHealthItem : public AItem
{
	GENERATED_BODY()
	
public:

	AHealthItem();
	virtual void Interact_Implementation(AEclipseRaptureCharacter* Character) override;
	
	
protected:
	virtual void Use(class AEclipseRaptureCharacter* Character) override;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Healing")
	float HealingAmount;
};
