// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "InteractableDoor.generated.h"

/**
 * 
 */
UCLASS()
class ECLIPSE_RAPTURE_API AInteractableDoor : public AItem
{
	GENERATED_BODY()
	
public:
	virtual void Interact_Implementation(AEclipseRaptureCharacter* Character) override;
	AInteractableDoor();
protected:
	void BeginPlay() override;

	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Interactable Door")
	TObjectPtr<USkeletalMeshComponent> DoorMesh;

	UFUNCTION()
	void HandleDoorInteraction(bool Opened);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Interactable Door")
	void OpenDoor();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Interactable Door")
	void CloseDoor();

	UPROPERTY(BlueprintReadOnly, Category = "Interactable Door")
	bool bIsOpen = false;

	UPROPERTY(BlueprintReadWrite, Category = "Interactable Door")
	FRotator OriginalRotation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interactable Door")
	TObjectPtr<UAnimMontage> OpenDoorMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interactable Door")
	TObjectPtr<UAnimMontage> CloseDoorMontage;

private:

	UAnimInstance* AnimInstance;
};
