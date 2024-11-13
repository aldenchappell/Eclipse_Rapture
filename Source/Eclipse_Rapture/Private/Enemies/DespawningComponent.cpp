// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Enemies/DespawningComponent.h"

UDespawningComponent::UDespawningComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	DespawnSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DespawnSphere"));
	DespawnSphere->SetSphereRadius(DespawnRadius);
}

void UDespawningComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UDespawningComponent::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bEnableDespawnRadius)
	{
		bShouldDespawn = false;
	}
}

void UDespawningComponent::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (bEnableDespawnRadius)
	{
		bShouldDespawn = true;
	}
}

void UDespawningComponent::CheckDespawn()
{
	if (!bShouldDespawn) return;

	if (APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		float DistanceToPlayer = FVector::Dist(GetOwner()->GetActorLocation(), PlayerPawn->GetActorLocation());

		if (bEnableDespawnRadius)
		{
			if (DistanceToPlayer > DespawnSphere->GetScaledSphereRadius())
			{
				GetOwner()->Destroy();
			}
		}
		else
		{
			GetOwner()->Destroy();
		}
	}
}

