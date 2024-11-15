// CoverObject.h

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CoverObject.generated.h"

UINTERFACE(MinimalAPI)
class UCoverObject : public UInterface
{
    GENERATED_BODY()
};

class ECLIPSE_RAPTURE_API ICoverObject
{
    GENERATED_BODY()

public:
    // BlueprintNativeEvent declaration with const reference
    UFUNCTION(BlueprintNativeEvent, Category = "Cover")
    void SetCoverPoints(const TArray<class AActor*>& NewCoverPoints);

    UFUNCTION(BlueprintNativeEvent, Category = "Cover")
    TArray<class AActor*> GetCoverPoints();

    UFUNCTION(BlueprintNativeEvent, Category = "Cover")
    void EnterCover(FVector CoverPoint);
};
