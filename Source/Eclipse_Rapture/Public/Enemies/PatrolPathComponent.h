// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrolPathComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ECLIPSE_RAPTURE_API UPatrolPathComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPatrolPathComponent();

	UPROPERTY(EditAnywhere)
	bool bEnablePatrolling = true;

	UPROPERTY(EditAnywhere)
	bool bEnableRandomPointPathfinding = true;

	UPROPERTY(EditAnywhere, Category = "Patrol Points")
	TArray<AActor*> PatrolPoints;

	UFUNCTION(Blueprintcallable)
	FVector GetWaypointLocation(int32 Index) const;

	UFUNCTION(BlueprintCallable)
	int32 GetNextWaypointIndex(int32 CurrentIndex) const;

protected:

	virtual void BeginPlay() override;
		
};
