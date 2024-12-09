// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FlashlightComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ECLIPSE_RAPTURE_API UFlashlightComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFlashlightComponent();
	
	UPROPERTY(EditDefaultsOnly, Category = "Flashlight | Flashlight Properties")
	TObjectPtr<class USpotLightComponent> Flashlight;

	UPROPERTY(EditDefaultsOnly, Category = "Flashlight | Flashlight Properties")
	TObjectPtr<class UStaticMeshComponent> FlashlightMesh;

	UFUNCTION(BlueprintCallable)
	void Attach(USkeletalMeshComponent* Mesh, FName SocketName);

	UFUNCTION(BlueprintCallable)
	void Enable();

	UFUNCTION(BlueprintCallable)
	void Disable();
protected:
	virtual void BeginPlay() override;

	
private:
	UPROPERTY()
	bool bHasFlashlight = false;

public:
	UFUNCTION(BlueprintCallable)
	void SetHasFlashlight(bool NewHasFlashlight);

	UFUNCTION(BlueprintCallable)
	bool GetHasFlashlight() const { return bHasFlashlight; }

	UFUNCTION(Blueprintcallable)
	bool GetIsEnabled() const { return FlashlightMesh->IsVisible(); }
};
