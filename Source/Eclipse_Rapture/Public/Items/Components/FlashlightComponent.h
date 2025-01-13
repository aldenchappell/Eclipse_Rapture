// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FlashlightComponent.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ECLIPSE_RAPTURE_API UFlashlightComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFlashlightComponent();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Flashlight | Flashlight Properties")
	TObjectPtr<class USpotLightComponent> Flashlight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Flashlight | Flashlight Properties")
	TObjectPtr<class UStaticMeshComponent> FlashlightMesh;

	UFUNCTION(BlueprintCallable)
	void Attach(USkeletalMeshComponent* Mesh, FName SocketName);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EnableFlashlight();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DisableFlashlight();
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
};
