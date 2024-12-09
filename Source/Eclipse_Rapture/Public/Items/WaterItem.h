// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "WaterItem.generated.h"

/**
 * 
 */
UCLASS()
class ECLIPSE_RAPTURE_API AWaterItem : public AItem
{
	GENERATED_BODY()
public:
	AWaterItem();

	virtual void Interact_Implementation(AEclipseRaptureCharacter* Character) override;

protected:
	virtual void Use(class AEclipseRaptureCharacter* Character) override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadonly, Category = "Healing")
	float ThirstHealAmount = 25.0f;

};
