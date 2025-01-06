#pragma once

#include "Interfaces/BuilderInterface.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuildingComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ECLIPSE_RAPTURE_API UBuildingComponent : public UActorComponent, public IBuilderInterface
{
    GENERATED_BODY()

public:
    UBuildingComponent();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float BuildingTraceLength = 500.f;

    virtual bool HasBuildingBlueprint_Implementation() override;
    virtual bool GetHasBuildingBlueprintEquipped_Implementation() override;
    virtual void BuildingBlueprintLineTrace_Implementation() override;
    virtual void SetBuildingItemBeingLookedAt_Implementation(AEclipseRaptureBuildingItem* BuildingItem) override;
	virtual AEclipseRaptureBuildingItem* GetBuildingItemBeingLookedAt_Implementation() override;
	virtual void SetBuildingHitLocation_Implementation(FVector HitLocation) override;
    virtual FVector GetBuildingHitLocation_Implementation() override;

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Building | Interfaces")
    FHitResult GetBuildingBlueprintHitResult();
    virtual FHitResult GetBuildingBlueprintHitResult_Implementation();

    UFUNCTION(BlueprintCallable, Category = "Building")
    void SetHasBuildingBlueprint(bool NewHasBuildlingBlueprint);

    UPROPERTY(BlueprintReadWrite)
    class AEclipseRaptureCharacter* OwningCharacter;

    UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Building | Testing")
    bool bDisableInteractionOnMaxUpgrade = false;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Building | Building Properties")
	bool bHasBuildingBlueprint = false;

    UPROPERTY(BlueprintReadWrite, Category = "Building | Building Properties")
    bool bBuildingBlueprintEquipped;
private:
    UPROPERTY()
    FHitResult LastHitResult;
    
    UPROPERTY()
    FVector BuildingHitLocation;

    UPROPERTY()
    class AEclipseRaptureBuildingItem* CurrentBuildingItem;
};