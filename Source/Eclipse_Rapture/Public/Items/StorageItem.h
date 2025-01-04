// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Character/EclipseRaptureCharacter.h"
#include "CoreMinimal.h"
#include "Items/Item.h"
#include "StorageItem.generated.h"

class AEclipseRaptureCharacter;
/**
 * 
 */
UCLASS()
class ECLIPSE_RAPTURE_API AStorageItem : public AItem
{
	GENERATED_BODY()
public:
	AStorageItem();

	virtual void Interact_Implementation(AEclipseRaptureCharacter* Character) override;
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UStaticMeshComponent> LidMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UInventoryComponent> InventoryComponent;
};
