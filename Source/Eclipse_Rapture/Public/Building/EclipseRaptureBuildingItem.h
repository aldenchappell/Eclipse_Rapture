// EclipseRaptureBuildingItem.h

#pragma once

#include "Building/BuildingTypes.h"
#include "Interfaces/BuildingInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EclipseRaptureBuildingItem.generated.h"

USTRUCT(BlueprintType)
struct FUpgradeRequirements
{
    GENERATED_BODY()

public:
    // Array of required items for this upgrade level
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrade")
    TArray<TSubclassOf<AItem>> RequiredItems;
};


UCLASS()
class ECLIPSE_RAPTURE_API AEclipseRaptureBuildingItem : public AActor, public IBuildingInterface
{
    GENERATED_BODY()

public:
    AEclipseRaptureBuildingItem();

    // Map of upgrade levels to their requirements
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Building | Upgrade")
    TMap<int32, FUpgradeRequirements> RequiredUpgradeItems;

protected:
    virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Building | Mesh")
	TObjectPtr<class UStaticMeshComponent> BuildingMesh;

    // Materials for each upgrade level
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building | Upgrade")
    TArray<class UMaterial*> Materials;


#pragma region Building Interface Implementations
	virtual void UpgradeBuilding_Implementation(FUpgradeInfo UpgradeInfo) override;
    virtual TArray<TSubclassOf<AItem>> GetRequiredUpgradeItems_Implementation(FUpgradeInfo UpgradeInfo) override;

#pragma endregion
};


