// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ThirstBar.generated.h"

/**
 * 
 */
UCLASS()
class ECLIPSE_RAPTURE_API UThirstBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> ThirstBar;

	UFUNCTION(BlueprintCallable)
	void SetThirstPercent(float Percent);

protected:
	void NativeConstruct() override;
};
