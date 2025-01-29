// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrolPoint.generated.h"

UCLASS()
class ECLIPSE_RAPTURE_API APatrolPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	APatrolPoint();

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	bool bEnablePointSphere = true;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	TObjectPtr<class USplineComponent> PatrolSpline;
};
