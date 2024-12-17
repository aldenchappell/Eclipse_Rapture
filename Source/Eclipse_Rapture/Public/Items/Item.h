// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Structures/FInventoryTypes.h"
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

	UPROPERTY(BlueprintReadonly, Category = "Item Properties | Player Reference")
	TObjectPtr<AEclipseRaptureCharacter> PlayerReference;

	virtual void Interact_Implementation(AEclipseRaptureCharacter* Character) override;

	UPROPERTY(Transient)
	class UWorld* World;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	bool bCanBeUsed = true;

	UFUNCTION()
	virtual void Use(class AEclipseRaptureCharacter* Character);

	UFUNCTION(BlueprintImplementableEvent)
	void OnUse(class AEclipseRaptureCharacter* Character);

#pragma region UI Implements
	//Text for using item(Equip, Consume, etc)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Properties")
	FText UseActionText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Properties")
	TObjectPtr<UStaticMesh> PickupMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Properties")
	TObjectPtr<UMaterialInterface> ThumbnailTexture;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Properties")
	TObjectPtr<UTexture2D> ItemUseIcon;

	//Name to show inside of inventory
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Properties")
	FText ItemDisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Properties", meta = (MultiLine = true))
	FText ItemDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Properties", meta = (ClampMin = 0.0))
	float ItemWeight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Properties", meta = (ClampMin = 0.0))
	int32 MaxStackSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Pickup Properties")
	FText ItemInteractionPrompt;

#pragma endregion

	UPROPERTY()
	TObjectPtr<class UInventoryComponent> OwningInventory;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Inventory Space")
	FInventorySpaceRequirements InventorySpaceRequired;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	EUseImpactType UseImpactType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	EMainItemUseDescriptionType MainItemUseDescriptionType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	ESecondaryItemUseDescriptionType SecondaryItemUseDescriptionType;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Properties")
	TObjectPtr<USkeletalMeshComponent> ItemSkeleton;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Collision")
	TObjectPtr<USphereComponent> SphereCollision;

	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	EItemType ItemType = EItemType::EIT_Pickup;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	EUsecaseType UsecaseType;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Item Properties")
	bool bDestroyOnPickup = false;

private:
	


public:	//Getters and Setters
	
	UFUNCTION(BlueprintPure, Blueprintcallable)
	FText GetItemDisplayName() const {return ItemDisplayName;}

	UFUNCTION(BlueprintPure, Blueprintcallable)
	EItemType GetItemType() const { return ItemType; }

	UFUNCTION(BlueprintPure, Blueprintcallable)
	EUsecaseType GetUsecaseType() const { return UsecaseType; }
};
