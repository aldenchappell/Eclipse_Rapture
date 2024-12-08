// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BuilderInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBuilderInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ECLIPSE_RAPTURE_API IBuilderInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Building | Interfaces")
	bool HasBuildingBlueprint();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Building | Interfaces")
	bool SetHasBuildingBlueprint(bool NewHasBlueprint);
};
