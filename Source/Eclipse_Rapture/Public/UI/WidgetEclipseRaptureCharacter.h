#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetEclipseRaptureCharacter.generated.h"

/**
 * Widget class for Eclipse Rapture's UI logic
 */

class UImage;
class UTextBlock;
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
protected:
    // Called when the widget is constructed
    virtual void NativeConstruct() override;

private:
    

    
};
