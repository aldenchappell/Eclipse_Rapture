// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyDataComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ECLIPSE_RAPTURE_API UEnemyDataComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEnemyDataComponent();

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Item Properties | Data")
	FDataTableRowHandle EnemyID;

	
};
