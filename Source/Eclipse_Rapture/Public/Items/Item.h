// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Character/EclipseRaptureCharacter.h"
#include "Interfaces/InteractInterface.h"
#include "ItemTypes.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"


class USphereComponent;
class USkeletalMeshComponent;
UCLASS()
class ECLIPSE_RAPTURE_API AItem : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	
	AItem();

	virtual void Interact_Implementation(AEclipseRaptureCharacter* Character) override;
protected:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Properties")
	TObjectPtr<UStaticMeshComponent> ItemMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Properties")
	TObjectPtr<USkeletalMeshComponent> ItemSkeleton;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	TObjectPtr<USphereComponent> SphereCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Properties")
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	FString ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	TObjectPtr<UTexture2D> InventoryThumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	float ItemWeight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	bool bStackable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	int32 MaxStackSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	int32 CurrentStackSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	bool bCanBeUsed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	bool bCanBeEquipped;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	bool bCanBeCrafted;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	bool bCanBeConsumed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	bool bCanBeRepaired;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	EItemType ItemType = EItemType::EIT_Pickup;

private:
	


public:	//Getters and Setters
	
	

};
