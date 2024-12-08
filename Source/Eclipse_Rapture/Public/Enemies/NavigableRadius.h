// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NavigableRadius.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ECLIPSE_RAPTURE_API UNavigableRadius : public UActorComponent
{
	GENERATED_BODY()

public:	
	UNavigableRadius();

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	class USphereComponent* NavigableRadiusSphere;

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	float Radius;

};
