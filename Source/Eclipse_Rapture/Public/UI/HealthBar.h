#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBar.generated.h"

/**
 * Health bar UI widget for displaying player's health
 */
UCLASS()
class ECLIPSE_RAPTURE_API UHealthBar : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(meta = (BindWidget))
    class UProgressBar* HealthBar;

    UFUNCTION(BlueprintCallable)
    void SetHealthPercent(float Percent);

protected:
    virtual void NativeConstruct() override;
};
