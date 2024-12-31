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


	//TODO: MOVE THESE VARIABLES TO PRIVATE!!
	UPROPERTY(BlueprintReadWrite, Category = "References")
	TObjectPtr<class UInventoryComponent> OwningInventory;


	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Item Pickup Properties")
	int32 MinItemDropAmount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Item Pickup Properties")
	int32 MaxItemDropAmount = 5;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Item Pickup Properties")
	void InitializeItemAmount();

	//how many of this object is rewarded to the player/is in this stack of item(s)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 ItemAmount = 0;

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


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	EItemType ItemType = EItemType::EIT_Pickup;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	EUsecaseType UsecaseType;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Item Properties")
	bool bDestroyOnPickup = false;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Item Properties", meta = (ExposeOnSpawn = "true"))
	TObjectPtr<UItemObject> ItemObject;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Inventory Space", meta = (ExposeOnSpawn = "true"))
	FInventorySpaceRequirements InventorySpaceRequired;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	EUseImpactType UseImpactType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	EMainItemUseDescriptionType MainItemUseDescriptionType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	ESecondaryItemUseDescriptionType SecondaryItemUseDescriptionType;

#pragma region UI Implements
	//Text for using item(Equip, Consume, etc)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item Properties")
	FText UseActionText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties", meta = (ExposeOnSpawn = "true"))
	TObjectPtr<UMaterialInterface> ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties", meta = (ExposeOnSpawn = "true"))
	TObjectPtr<UMaterialInterface> ItemIconRotated;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Item Properties")
	void Rotate();

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Properties")
	FItemData ItemData;
private:

	UPROPERTY()
	bool bItemIconRotated;

public:	//Getters and Setters
	UFUNCTION(BlueprintPure, BlueprintCallable)
	FItemData GetItemData() const { return ItemData; }

	UFUNCTION(BlueprintPure, Blueprintcallable)
	int32 GetItemAmount() const { return ItemAmount; }

	UFUNCTION(Blueprintcallable)
	void SetItemAmount(int32 NewItemAmount);

	UFUNCTION(BlueprintPure, Blueprintcallable)
	EItemType GetItemType() const { return ItemType; }

	UFUNCTION(BlueprintPure, Blueprintcallable)
	EUsecaseType GetUsecaseType() const { return UsecaseType; }

	UFUNCTION(BlueprintCallable)
	void SetItemObject(UItemObject* NewItemObject);

	UFUNCTION(BlueprintPure, Blueprintcallable)
	FText GetItemDisplayName() const { return ItemDisplayName; }

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Blueprintcallable)
	FInventorySpaceRequirements GetInventorySpaceRequirements();

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, BlueprintCallable)
	class UMaterialInterface* GetItemIcon() const;

	UFUNCTION(BlueprintPure, BlueprintCallable)
	bool GetIsRotated() const { return bItemIconRotated; }

	UFUNCTION(BlueprintCallable)
	void SetIsRotated(bool bNewIsRotated);

	UFUNCTION(BlueprintPure, BlueprintCallable)
	float GetItemWeight() const { return ItemWeight; }

	UFUNCTION(BlueprintPure, BlueprintCallable)
	int32 GetMaxStackSize() const { return MaxStackSize; }

	UFUNCTION(BlueprintPure, BlueprintCallable)
	FText GetItemDescription() const { return ItemDescription; }

	UFUNCTION(BlueprintPure, BlueprintCallable)
	FText GetUseActionText() const { return UseActionText; }

	UFUNCTION(BlueprintPure, BlueprintCallable)
	FText GetItemInteractionPrompt() const { return ItemInteractionPrompt; }

	UFUNCTION(BlueprintCallable, Category = "Item Properties")
	UTexture2D* GetItemUseIcon() const { return ItemUseIcon; }

	UFUNCTION(BlueprintCallable, Category = "Item Properties")
	EUseImpactType GetUseImpactType() const { return UseImpactType; }

	UFUNCTION(BlueprintCallable, Category = "Item Properties")
	EMainItemUseDescriptionType GetMainItemUseDescriptionType() const { return MainItemUseDescriptionType; }

	UFUNCTION(BlueprintCallable, Category = "Item Properties")
	ESecondaryItemUseDescriptionType GetSecondaryItemUseDescriptionType() const { return SecondaryItemUseDescriptionType; }
};
