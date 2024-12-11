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
    // Array of required item types for this upgrade level
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrade")
    TArray<TSubclassOf<class AItem>> RequiredItems;

    // Array of quantities matching the RequiredItems
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrade")
    TArray<int32> RequiredQuantities;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrade")
	EUpgradeType SUpgradeType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrade")
	EUpgradeCostType SUpgradeCostType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrade")
    EBuildingType SBuildingType;
};



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingUpgrade, FUpgradeInfo, UpgradeInfo);
UCLASS()
class ECLIPSE_RAPTURE_API AEclipseRaptureBuildingItem : public AActor, public IBuildingInterface
{
    GENERATED_BODY()

public:
    AEclipseRaptureBuildingItem();

    // Map of upgrade levels to their requirements
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Building | Upgrade")
    TMap<int32, FUpgradeRequirements> UpgradeRequirements;

    // Current upgrade level
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building | Upgrade")
    int32 CurrentUpgradeLevel;

    // Maximum upgrade level
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building | Upgrade")
    int32 MaxUpgradeLevel;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Building | Upgrade")
    FOnBuildingUpgrade OnBuildingUpgrade;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrade")
    EBuildingType BuildingType;
protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Building | Mesh")
    TObjectPtr<class UStaticMeshComponent> BuildingMesh;

    // Materials for each upgrade level
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building | Upgrade")
    TArray<class UMaterial*> Materials;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building | Messages")
    bool bShowDebugMessages;

#pragma region Building Interface Implementations
    virtual void UpgradeBuilding_Implementation(FUpgradeInfo UpgradeInfo, FUpgradeResults& Result) override;
    virtual TArray<TSubclassOf<AItem>> GetRequiredUpgradeItems_Implementation(FUpgradeInfo UpgradeInfo) override;
	virtual EBuildingType GetBuildingType_Implementation() override;
#pragma endregion
};
