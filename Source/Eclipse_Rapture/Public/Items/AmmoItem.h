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

protected:

	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	virtual void Destroyed() override;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Drop Properties")
	int32 MinAmount = 5;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Drop Properties")
	int32 MaxAmount = 25;

	UPROPERTY(BlueprintReadWrite, Category = "Drop Properties")
	int32 AmmoDropAmount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Drop Properties")
	bool bEnableRandomDropAmount = true;


};
