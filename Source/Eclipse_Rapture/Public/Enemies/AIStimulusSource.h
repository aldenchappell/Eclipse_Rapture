// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "AIStimulusSource.generated.h"

/**
 * 
 */
UCLASS()
class ECLIPSE_RAPTURE_API UAIStimulusSource : public UAIPerceptionStimuliSourceComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsonly, BlueprintReadonly, Category = "AI | Stimulus")
	TObjectPtr<class UAIStimulusSource> StimulusSource;
	
};
