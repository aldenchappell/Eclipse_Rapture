// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponDataComponent.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ECLIPSE_RAPTURE_API UWeaponDataComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponDataComponent();

	//Weapon ID Data Table Value
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Item Properties | Data")
	FDataTableRowHandle WeaponID;
protected:
	virtual void BeginPlay() override;

private:

		
};
