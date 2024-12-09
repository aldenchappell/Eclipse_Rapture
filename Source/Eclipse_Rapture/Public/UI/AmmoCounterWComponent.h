// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "AmmoCounterWComponent.generated.h"

/**
 * 
 */
UCLASS()
class ECLIPSE_RAPTURE_API UAmmoCounterWComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	
	UFUNCTION()
	void SetAmmoCounterText(int CurrentAmmo, int MaxAmmo);

private:

	class UAmmoCounter* AmmoCounter;
};
