// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
#include "Components/SphereComponent.h"
#include "Interfaces/IPhysicsComponent.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = false;
	

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	SetRootComponent(ItemMesh);

	ItemMesh->SetSimulatePhysics(true);
	ItemMesh->SetMassOverrideInKg(NAME_None, 60.f);
	ItemMesh->SetLinearDamping(.25f);
	ItemMesh->SetAngularDamping(.25f);

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(GetRootComponent());
	SphereCollision->SetSphereRadius(125.f);
}

void AItem::Interact_Implementation(AEclipseRaptureCharacter* Character)
{
}



void AItem::BeginPlay()
{
	Super::BeginPlay();
	
	//bind overlap events to overlap delegates
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnSphereOverlap);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &AItem::OnSphereEndOverlap);
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEclipseRaptureCharacter* Character = Cast<AEclipseRaptureCharacter>(OtherActor);
	if (Character)
	{
		Character->SetCurrentlyOverlappingItem(this);
	}
}

void AItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AEclipseRaptureCharacter* Character = Cast<AEclipseRaptureCharacter>(OtherActor);
	if (Character)
	{
		Character->SetCurrentlyOverlappingItem(nullptr);
	}
}