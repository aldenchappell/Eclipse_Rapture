// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
#include "Components/SphereComponent.h"
#include "Interfaces/IPhysicsComponent.h"
#include "Character/PlayerMain.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = false;
	

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(GetRootComponent());

	ItemMesh->SetSimulatePhysics(true);
	ItemMesh->SetMassOverrideInKg(NAME_None, 60.f);
	ItemMesh->SetLinearDamping(.25f);
	ItemMesh->SetAngularDamping(.25f);

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(ItemMesh);
	SphereCollision->SetSphereRadius(125.f);

	ItemSkeleton = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ItemSkeleton"));
	ItemSkeleton->SetupAttachment(ItemMesh);

	ItemWeight = 1.f;
	ItemDisplayName = FText::FromString("Item");
	UseActionText = FText::FromString("Use");
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	ItemClass = GetClass();
	// Get the player character reference
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		APawn* PlayerPawn = PlayerController->GetPawn();
		PlayerReference = Cast<AEclipseRaptureCharacter>(PlayerPawn);
	}

	if (!PlayerReference)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerReference is NULL in AItem::BeginPlay."));
	}

	// Bind overlap events
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnSphereOverlap);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &AItem::OnSphereEndOverlap);
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::Interact_Implementation(AEclipseRaptureCharacter* Character)
{

}

void AItem::Use(AEclipseRaptureCharacter* Character)
{
	if (!bCanBeUsed) return;
}

void AItem::Rotate()
{
	bRotated = !bRotated;
}

void AItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerMain* Character = Cast<APlayerMain>(OtherActor);
	if (Character)
	{
		Character->SetCurrentlyOverlappingItem(this);
	}
}

void AItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerMain* Character = Cast<APlayerMain>(OtherActor);
	if (Character)
	{
		Character->SetCurrentlyOverlappingItem(nullptr);
	}
}

FInventoryDimensions AItem::GetInventoryDimensions()
{
	if (bRotated)
	{
		return InventoryDimensions;
	}
	else
	{
		return FInventoryDimensions(InventoryDimensions.DimensionsY, InventoryDimensions.DimensionsX);
	}
}

UMaterialInterface* AItem::GetItemIcon() const
{
	if (!ItemIcon || !ItemIconRotated) return nullptr;

	return bRotated ? ItemIconRotated : ItemIcon;
}
