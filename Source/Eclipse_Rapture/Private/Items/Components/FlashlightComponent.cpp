// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Components/FlashlightComponent.h"
#include "Components/SpotLightComponent.h"

UFlashlightComponent::UFlashlightComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UFlashlightComponent::Attach(USkeletalMeshComponent* Mesh, FName SocketName)
{
	if (!bHasFlashlight) return;

	if (FlashlightMesh && Mesh && Flashlight)
	{
		FlashlightMesh->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
	}
}


void UFlashlightComponent::EnableFlashlight_Implementation() {}
void UFlashlightComponent::DisableFlashlight_Implementation() {}
	
void UFlashlightComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UFlashlightComponent::SetHasFlashlight(bool NewHasFlashlight)
{
	this->bHasFlashlight = NewHasFlashlight;
}
