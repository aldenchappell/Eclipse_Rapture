// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SatietyBar.generated.h"

/**
 * 
 */
UCLASS()
class ECLIPSE_RAPTURE_API USatietyBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> SatietyBar;

	UFUNCTION(BlueprintCallable)
	void SetSatietyPercent(float Percent);
protected:
	void NativeConstruct() override;
};
