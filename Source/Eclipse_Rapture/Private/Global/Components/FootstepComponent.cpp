// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Components/FootstepComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
UFootstepComponent::UFootstepComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	
}

void UFootstepComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UFootstepComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UFootstepComponent::PlayFootstepSound(AActor* Character, TArray<USoundBase*> FootstepSounds)
{
	if (FootstepSounds.Num() > 0)
	{
		int32 RandomSoundIndex = FMath::RandRange(0, FootstepSounds.Num() - 1);
		USoundBase* RandomFootstepSound = FootstepSounds[RandomSoundIndex];


		if (RandomFootstepSound)
		{
			UGameplayStatics::PlaySoundAtLocation(
				GetWorld(),
				RandomFootstepSound,
				CalcFootstepLocation(Character),
				FootstepVolumeMultiplier,
				FootstepPitchMultiplier);
		}
	}
}

void UFootstepComponent::FootstepTrace(AActor* Character)
{
	FHitResult HitInfo;
	FVector TraceStart = Character->GetActorLocation();
	FVector TraceEnd = TraceStart + FVector(0.f, 0.f, FootstepTraceDistance);

	GetWorld()->LineTraceSingleByChannel(
		HitInfo,
		TraceStart,
		TraceEnd,
		ECollisionChannel::ECC_Visibility);

	if (HitInfo.bBlockingHit)
	{
		//enable bool
		//play sound
		//reset timer
	}
}

void UFootstepComponent::ResetFootstepTimer()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(FootstepTimerHandle);
	}
}

FVector UFootstepComponent::CalcFootstepLocation(AActor* Character)
{
	if (Character)
	{
		FVector CharacterPosition = Character->GetActorLocation();
		FVector FootstepPosition = CharacterPosition + FVector(0.f, 0.f, Character->GetActorForwardVector().Z + FootstepZOffset);

		return FootstepPosition;
	}
}
