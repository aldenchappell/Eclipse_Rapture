// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interfaces/Unlockable.h"
#include "CoreMinimal.h"
#include "Items/Item.h"
#include "InteractableDoor.generated.h"


class UInventoryComponent;


UCLASS()
class ECLIPSE_RAPTURE_API AInteractableDoor : public AItem, public IUnlockable
{
	GENERATED_BODY()
	
public:
	virtual void Interact_Implementation(AEclipseRaptureCharacter* Character) override;
	AInteractableDoor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Logic")
	bool bIsLocked = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction Logic")
	FName RequiredItemIDToUnlock;
protected:
	void BeginPlay() override;

	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	

	UFUNCTION()
	void HandleDoorInteraction(bool Opened);

	UFUNCTION()
	void Unlock_Implementation(UInventoryComponent* CharacterInventory);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Interactable Door")
	void OpenDoor();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Interactable Door")
	void CloseDoor();

	UPROPERTY(BlueprintReadOnly, Category = "Interactable Door")
	bool bIsOpen = false;

	UPROPERTY(BlueprintReadWrite, Category = "Interactable Door")
	FRotator OriginalRotation;

private:

	UAnimInstance* AnimInstance;
};
