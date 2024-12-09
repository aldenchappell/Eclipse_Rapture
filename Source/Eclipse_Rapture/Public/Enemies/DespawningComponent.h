// DespawningComponent.h

#pragma once


#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DespawningComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ECLIPSE_RAPTURE_API UDespawningComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UDespawningComponent();

    UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Despawning")
    bool bEnableDespawnRadius = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Despawning")
    float DespawnDelay = 5.0f;  // Time in seconds before destruction after death

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Despawning")
    TObjectPtr<class USphereComponent> DespawnSphere;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Despawning")
    float DespawnRadius = 5000.f;

	//Called upon death to start the despawn timer
    UFUNCTION(BlueprintCallable, Category = "Despawning")
    void StartDespawnTimer();

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
    bool bShouldDespawn = false;
    FTimerHandle DespawnTimerHandle;

    void CheckDespawn();
};
