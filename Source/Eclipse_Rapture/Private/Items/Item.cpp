// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
#include "Components/SphereComponent.h"
#include "Interfaces/IPhysicsComponent.h"
#include "Character/PlayerMain.h"
#include "Items/ItemObject.h"

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

	ItemWeight = 1.f;
	ItemDisplayName = FText::FromString("Item");
	UseActionText = FText::FromString("Use");
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
;	// Get the player character reference
	/*APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		APawn* PlayerPawn = PlayerController->GetPawn();
		PlayerReference = Cast<AEclipseRaptureCharacter>(PlayerPawn);
	}

	if (!PlayerReference)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerReference is NULL in AItem::BeginPlay."));
	}*/

	// Bind overlap events
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnSphereOverlap);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &AItem::OnSphereEndOverlap);
}

void AItem::InitializeItemAmount_Implementation()
{
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


void AItem::SetItemAmount(int32 NewItemAmount)
{
	ItemAmount = NewItemAmount;
}

void AItem::SetItemObject(UItemObject* NewItemObject)
{
	ItemObject = NewItemObject;
}

UMaterialInterface* AItem::GetItemIcon_Implementation() const
{
	return nullptr;
}



void AItem::Rotate_Implementation()
{
}

FInventorySpaceRequirements AItem::GetInventorySpaceRequirements_Implementation()
{
	return InventorySpaceRequired;
}

void AItem::SetIsRotated(bool bNewIsRotated)
{
	bItemIconRotated = bNewIsRotated;
}
