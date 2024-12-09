// EclipseRaptureBuildingItem.h

#pragma once

#include "Building/BuildingTypes.h"
#include "Interfaces/BuildingInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EclipseRaptureBuildingItem.generated.h"

UCLASS()
class ECLIPSE_RAPTURE_API AEclipseRaptureBuildingItem : public AActor, public IBuildingInterface
{
    GENERATED_BODY()

public:
    AEclipseRaptureBuildingItem();

protected:
    virtual void BeginPlay() override;

    //Upgrade type, upgrade level (0 = Wood, 1 = Brick, 2 = Metal, 3 = Reinforced) 
    UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Building | Building Materials")
	TMap<EUpgradeType, int32> BuildingMaterials;

    //Upgrade Cost (Will be used to decipher what items the player needs in order to upgrade this building item.
    UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Building | Building Materials")
	EUpgradeCostType UpgradeCostType;


};
