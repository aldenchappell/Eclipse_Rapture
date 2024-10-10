
#include "Global/Components/FootstepComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

UFootstepComponent::UFootstepComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	FootstepDelay = .6f;
	FootstepVolumeMultiplier = 1.f;
	FootstepPitchMultiplier = 1.f;
	FootstepZOffset = 0.f;
	FootstepTraceDistance = 50.f;
	bShouldPlaySound = false;
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


		if (bShouldPlaySound && RandomFootstepSound)
		{
			UGameplayStatics::PlaySoundAtLocation(
				GetWorld(),
				RandomFootstepSound,
				CalcFootstepLocation(Character),
				FootstepVolumeMultiplier,
				FootstepPitchMultiplier);

			ResetFootstepTimer();
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
		bShouldPlaySound = true;
		//set surface type
		CurrentSurfaceType = HitInfo.PhysMaterial.Get();
		//set footstep location
		FootstepLocation = CalcFootstepLocation(Character);

		//play sound
		switch (CurrentSurfaceType->SurfaceType)
		{
		case EPhysicalSurface::SurfaceType1:
			if (DryGrassFootstepSounds.Num() > 0)
			{
				PlayFootstepSound(Character, DryGrassFootstepSounds);
			}
			break;
		case EPhysicalSurface::SurfaceType2:
			if (WetGrassFootstepSounds.Num() > 0)
			{
				PlayFootstepSound(Character, WetGrassFootstepSounds);
			}
			break;
		case EPhysicalSurface::SurfaceType3:
			if (DirtFootstepSounds.Num() > 0)
			{
				PlayFootstepSound(Character, DirtFootstepSounds);
			}
			break;
		case EPhysicalSurface::SurfaceType4:
			if (StoneFootstepSounds.Num() > 0)
			{
				PlayFootstepSound(Character, StoneFootstepSounds);
			}
			break;
		case EPhysicalSurface::SurfaceType5:
			if (WoodFootstepSounds.Num() > 0)
			{
				PlayFootstepSound(Character, WoodFootstepSounds);
			}
			break;
		case EPhysicalSurface::SurfaceType6:
			if (MetalFootstepSounds.Num() > 0)
			{
				PlayFootstepSound(Character, MetalFootstepSounds);
			}
			break;
		case EPhysicalSurface::SurfaceType7:
			if (WaterFootstepSounds.Num() > 0)
			{
				PlayFootstepSound(Character, WaterFootstepSounds);
			}
			break;
		case EPhysicalSurface::SurfaceType8:
			if (SticksFootstepSounds.Num() > 0)
			{
				PlayFootstepSound(Character, SticksFootstepSounds);
			}
			break;
		}

		if (GetWorld())
		{
			GetWorld()->GetTimerManager().SetTimer(FootstepTimerHandle, this, &UFootstepComponent::ResetFootstepTimer, FootstepDelay, false);
		}
	}
	else
	{
		bShouldPlaySound = false;
		CurrentSurfaceType = nullptr;
	}
}

void UFootstepComponent::ResetFootstepTimer()
{
	if (GetWorld())
	{
		bShouldPlaySound = false;
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
	return FVector::ZeroVector;
}

EPhysicalSurface UFootstepComponent::GetSurfaceType(FHitResult HitInfo)
{
	return HitInfo.PhysMaterial->SurfaceType;
}