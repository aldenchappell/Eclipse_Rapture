#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetEclipseRaptureCharacter.generated.h"

/**
 * Widget class for Eclipse Rapture's UI logic
 */

class UImage;
class UTextBlock;
class UProgressBar;
UCLASS()
class ECLIPSE_RAPTURE_API UWidgetEclipseRaptureCharacter : public UUserWidget
{
    GENERATED_BODY()

public:

    UPROPERTY(BlueprintReadonly, meta = (BindWidget))
    TObjectPtr<UTextBlock> AmmoCounterText;

    UPROPERTY(BlueprintReadonly, meta = (BindWidget))
    TObjectPtr<UImage> CrosshairImage;

    UPROPERTY(BlueprintReadonly, meta = (BindWidget))
    TObjectPtr<UImage> MantleImage;

    UPROPERTY(BlueprintReadonly, meta = (BindWidget))
    TObjectPtr<class UHealthBar> HealthBar;

    UPROPERTY(BlueprintReadonly, meta = (BindWidget))
    TObjectPtr<class USatietyBar> SatietyBar;

    UPROPERTY(BlueprintReadonly, meta = (BindWidget))
    TObjectPtr<class UThirstBar> ThirstBar;

    UPROPERTY(BlueprintReadonly)
    TObjectPtr<class UWidgetInventoryGrid> WidgetInventoryGrid;

protected:
    // Called when the widget is constructed
    virtual void NativeConstruct() override;
private:
    

    
};
