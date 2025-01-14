// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Structures/FInventoryTypes.h"
#include "Character/EclipseRaptureCharacter.h"
#include "Interfaces/InteractInterface.h"
#include "ItemTypes.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class UItemObject;
class USphereComponent;
class USkeletalMeshComponent;
class UItemDataComponent;
UCLASS()
class ECLIPSE_RAPTURE_API AItem : public AActor, public IInteractInterface
{
	GENERATED_BODY()

public:
	AItem();
	virtual void Interact_Implementation(AEclipseRaptureCharacter* Character) override;

	UPROPERTY(Transient)
	class UWorld* World;

	UPROPERTY(BlueprintReadWrite, Category = "References")
	TObjectPtr<class UInventoryComponent> OwningInventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item Properties | Data")
	TObjectPtr<UItemDataComponent> DataComponent;

protected:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	

	UPROPERTY(BlueprintReadonly)
	TObjectPtr<class AEclipseRaptureCharacter> OverlappingCharacter;

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Properties")
	TObjectPtr<UStaticMeshComponent> ItemMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Collision")
	TObjectPtr<USphereComponent> SphereCollision;	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Properties")
	TObjectPtr<UTexture2D> ItemUseIcon;

#pragma endregion
};
