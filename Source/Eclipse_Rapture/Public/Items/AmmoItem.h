// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "AmmoItem.generated.h"

/**
 * 
 */
UCLASS()
class ECLIPSE_RAPTURE_API AAmmoItem : public AItem
{
	GENERATED_BODY()
	
public:
	AAmmoItem();
	virtual void Interact_Implementation(AEclipseRaptureCharacter* Character) override;

	virtual void Use(class AEclipseRaptureCharacter* Character) override;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Drop Properties")
	int32 MinAmount = 5;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Drop Properties")
	int32 MaxAmount = 25;

	UPROPERTY()
	int32 AmmoDropAmount;

	UFUNCTION()
	void InitializeAmmoDrop();


};
