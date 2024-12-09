#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BuilderInterface.generated.h"

UINTERFACE(MinimalAPI)
class UBuilderInterface : public UInterface
{
    GENERATED_BODY()
};

class ECLIPSE_RAPTURE_API IBuilderInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Building | Interfaces")
    bool HasBuildingBlueprint();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Building | Interfaces")
    void SetHasBuildingBlueprint(bool NewHasBlueprint);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Building | Interfaces")
    bool GetHasBuildingBlueprintEquipped();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Building | Interfaces")
    void BuildingBlueprintLineTrace();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Building | Interfaces")
    void SetBuildingItemBeingLookedAt(AEclipseRaptureBuildingItem* BuildingItem);
};
