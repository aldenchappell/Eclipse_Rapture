// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Character/EclipseRaptureCharacter.h"
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Unlockable.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UUnlockable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ECLIPSE_RAPTURE_API IUnlockable
{
	GENERATED_BODY()

public:

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    void Unlock(UInventoryComponent* CharacterInventory);
};
