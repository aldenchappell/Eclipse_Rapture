// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DespawningComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ECLIPSE_RAPTURE_API UDespawningComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDespawningComponent();

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Despawning")
	bool bEnableDespawnRadius = true;

	bool bShouldDespawn = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Despawning")
	TObjectPtr<class USphereComponent> DespawnSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Despawning")
	float DespawnRadius = 5000.f;

	UFUNCTION(Blueprintcallable)
	void CheckDespawn();

protected:
	
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

		
};
