// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AnimBPInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAnimBPInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ECLIPSE_RAPTURE_API IAnimBPInterface
{
	GENERATED_BODY()

	
public:
	/// <summary>
	/// how much the gun recoils upwards
	/// how much rotation to the side when shooting
	/// back towards the player
	/// sideways from the player
	/// how much the gun recoils upwards
	/// </summary>
	/// <param name="RecoilMultiplier"></param>
	/// <param name="SideRecoilMultiplier"></param>
	/// <param name="KickbackRecoilMultiplier"></param>
	/// <param name="KicksideRecoilMultiplier"></param>
	/// <param name="KickupRecoilMultiplier"></param>
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damage")
	void IF_Recoil(
		float RecoilMultiplier,
		float SideRecoilMultiplier,
		float KickbackRecoilMultiplier, 
		float KicksideRecoilMultiplier, 
		float KickupRecoilMultiplier); 
};
