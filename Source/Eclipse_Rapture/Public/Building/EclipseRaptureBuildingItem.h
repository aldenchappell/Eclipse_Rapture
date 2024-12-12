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
    EUpgradeType UpgradeType;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingUpgrade, FUpgradeInfo, UpgradeInfo);

UCLASS()
class ECLIPSE_RAPTURE_API AEclipseRaptureBuildingItem : public AActor, public IBuildingInterface
{
    GENERATED_BODY()

public:
    AEclipseRaptureBuildingItem();

    // Map of upgrade types to their requirements
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Building | Upgrade")
    TMap<EUpgradeType, FUpgradeRequirements> UpgradeRequirements;

    // Current upgrade type
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building | Upgrade")
    EUpgradeType CurrentUpgradeType;

    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Building | Upgrade")
    FOnBuildingUpgrade OnBuildingUpgrade;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Building | Mesh")
    TObjectPtr<class UStaticMeshComponent> BuildingMesh;

    // Materials for each upgrade type
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building | Upgrade")
    TMap<EUpgradeType, class UMaterialInstance*> Materials;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building | Messages")
    bool bShowDebugMessages;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Building | Mesh")
	EBuildingType BuildingType;

#pragma region Building Interface Implementations
    virtual void UpgradeBuilding_Implementation(FUpgradeInfo UpgradeInfo, FUpgradeResults& Result) override;
    
    virtual TArray<TSubclassOf<AItem>> GetRequiredUpgradeItems_Implementation(FUpgradeInfo UpgradeInfo) override;
    virtual AEclipseRaptureBuildingItem* GetBuildingItem_Implementation() override;
    virtual EBuildingType GetBuildingType_Implementation() override;
#pragma endregion

private:
    void ValidateRequiredItems(FUpgradeRequirements& Requirements, FString& UpgradeTypeDisplayName, FUpgradeResults& Result);
    void DeductInventoryItems(FUpgradeRequirements& Requirements, FUpgradeInfo& UpgradeInfo);
    void ApplyUpgradedMaterial(FUpgradeInfo& UpgradeInfo, FString& UpgradeTypeDisplayName, FUpgradeResults& Result);
    void CheckInventory(FUpgradeRequirements& Requirements, FUpgradeInfo& UpgradeInfo, FUpgradeResults& Result);
};
