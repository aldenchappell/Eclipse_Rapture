// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RaptureGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ECLIPSE_RAPTURE_API URaptureGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Instance Properties")
	TObjectPtr<class USaveData_PlayerData> PlayerSaveData;
protected:

};
