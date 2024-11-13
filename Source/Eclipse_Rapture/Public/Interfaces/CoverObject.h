// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CoverObject.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCoverObject : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ECLIPSE_RAPTURE_API ICoverObject
{
	GENERATED_BODY()

	
public:

	UFUNCTION(BlueprintNativeEvent, Category = Cover)
	void EnterCover(FVector CoverPoint);
};
