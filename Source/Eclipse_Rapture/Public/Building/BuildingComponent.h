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

    UPROPERTY(EditDefaultsOnly, BlueprintReadonly)
    class UStaticMeshComponent* BlueprintMesh;
protected:
    virtual void BeginPlay() override;



    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float BuildingTraceLength = 500.f;

    virtual bool HasBuildingBlueprint_Implementation() override;
    virtual bool GetHasBuildingBlueprintEquipped_Implementation() override;
    virtual void SetHasBuildingBlueprint_Implementation(bool NewHasBlueprint) override;
    virtual void BuildingBlueprintLineTrace_Implementation() override;
    virtual void SetBuildingItemBeingLookedAt_Implementation(AEclipseRaptureBuildingItem* BuildingItem) override;

    UPROPERTY()
    class AEclipseRaptureBuildingItem* CurrentBuildingItem;

private:

    UPROPERTY()
    class AEclipseRaptureCharacter* OwningCharacter;
};