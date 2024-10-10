// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "FootstepComponent.generated.h"

class USoundBase;
class UPhysicalMaterial;


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ECLIPSE_RAPTURE_API UFootstepComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UFootstepComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Footsteps | Footstep Properties")
	float FootstepDelay = .6f;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Footsteps | Footstep Properties")
	float FootstepVolumeMultiplier = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Footsteps | Footstep Properties")
	float FootstepPitchMultiplier = 1.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Footsteps | Footstep Properties")
	FTimerHandle FootstepTimerHandle;

#pragma region Sounds
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Footsteps | Footstep Sounds")
	TArray<TObjectPtr<USoundBase>> DryGrassFootstepSounds;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Footsteps | Footstep Sounds")
	TArray<TObjectPtr<USoundBase>> WetGrassFootstepSounds;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Footsteps | Footstep Sounds")
	TArray<TObjectPtr<USoundBase>> DirtFootstepSounds;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Footsteps | Footstep Sounds")
	TArray<TObjectPtr<USoundBase>> StoneFootstepSounds;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Footsteps | Footstep Sounds")
	TArray<TObjectPtr<USoundBase>> WoodFootstepSounds;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Footsteps | Footstep Sounds")
	TArray<TObjectPtr<USoundBase>> MetalFootstepSounds;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Footsteps | Footstep Sounds")
	TArray<TObjectPtr<USoundBase>> WaterFootstepSounds;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Footsteps | Footstep Sounds")
	TArray<TObjectPtr<USoundBase>> SticksFootstepSounds;

#pragma endregion

	UFUNCTION(BlueprintCallable, Category = "Footsteps | Footstep Functions")
	void PlayFootstepSound(AActor* Character, TArray<USoundBase*> FootstepSounds);

	UFUNCTION(BlueprintCallable, Category = "Footsteps | Footstep Functions")
	void FootstepTrace(AActor* Character);

	UPROPERTY(BlueprintReadOnly, Category = "Footsteps | Footstep Properties")
	FVector FootstepLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Footsteps | Footstep Properties")
	float FootstepZOffset = -80.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Footsteps | Footstep Properties")
	float FootstepTraceDistance = 50.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Footsteps | Footstep Properties")
	TObjectPtr<UPhysicalMaterial> CurrentSurfaceType;

private:
	UFUNCTION()
	void ResetFootstepTimer();

	UFUNCTION()
	FVector CalcFootstepLocation(AActor* Character);

	UFUNCTION()
	EPhysicalSurface GetSurfaceType(FHitResult HitInfo);

	bool bShouldPlaySound = false;


public:	//Getters and Setters


};
