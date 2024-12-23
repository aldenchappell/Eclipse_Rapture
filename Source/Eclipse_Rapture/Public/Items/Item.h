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



	UPROPERTY(BlueprintReadWrite, Category = "References")
	TObjectPtr<class UInventoryComponent> OwningInventory;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Properties", meta = (ExposeOnSpawn = "true"));
	TSubclassOf<AItem> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Item Properties", meta = (ExposeOnSpawn = "true"))
	TObjectPtr<UItemObject> ItemObject;
private:



public:	//Getters and Setters

	

	UFUNCTION(BlueprintPure, Blueprintcallable)
	EItemType GetItemType() const { return ItemType; }

	UFUNCTION(BlueprintPure, Blueprintcallable)
	EUsecaseType GetUsecaseType() const { return UsecaseType; }

	UFUNCTION(BlueprintPure, Blueprintcallable)
	TSubclassOf<AItem> GetItemClass() const { return ItemClass; }

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Blueprintcallable)
	UItemObject* GetItemObject() const;

	UFUNCTION(BlueprintCallable)
	void SetItemObject(UItemObject* NewItemObject);
};
