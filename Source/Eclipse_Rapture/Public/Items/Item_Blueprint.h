// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Item_Blueprint.generated.h"

/**
 * 
 */
UCLASS()
class ECLIPSE_RAPTURE_API AItem_Blueprint : public AItem
{
	GENERATED_BODY()
	

public:
	AItem_Blueprint();
	virtual void Interact_Implementation(AEclipseRaptureCharacter* Character) override;

protected:
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
};
