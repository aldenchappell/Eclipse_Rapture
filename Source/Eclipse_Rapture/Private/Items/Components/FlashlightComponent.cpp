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

void UFlashlightComponent::Enable()
{
	if (!bHasFlashlight) return;

	if (FlashlightMesh && Flashlight)
	{
		FlashlightMesh->SetVisibility(true);
		Flashlight->SetVisibility(true);
	}
}

void UFlashlightComponent::Disable()
{
	FlashlightMesh->SetVisibility(false);
	Flashlight->SetVisibility(false);
}
	
void UFlashlightComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UFlashlightComponent::SetHasFlashlight(bool NewHasFlashlight)
{
	this->bHasFlashlight = NewHasFlashlight;
}
