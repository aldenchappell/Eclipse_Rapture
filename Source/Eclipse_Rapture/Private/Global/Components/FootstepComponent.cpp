
#include "Global/Components/FootstepComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Character/EclipseRaptureCharacter.h"

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

    // Cache the character reference once at the beginning
    CachedCharacter = Cast<AEclipseRaptureCharacter>(GetOwner());
    if (!CachedCharacter)
    {
        UE_LOG(LogTemp, Warning, TEXT("UFootstepComponent: Owner is not an AEclipseRaptureCharacter or derived from it."));
    }
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
    if (Character)
    {
        FHitResult HitInfo;
        FVector TraceStart = Character->GetActorLocation();
        FVector TraceEnd = TraceStart - FVector(0.f, 0.f, FootstepTraceDistance); // Tracing downwards

        if (GetWorld()->LineTraceSingleByChannel(
            HitInfo,
            TraceStart,
            TraceEnd,
            ECollisionChannel::ECC_Visibility))
        {
            // Check if the hit has a valid physical material
            if (HitInfo.PhysMaterial.IsValid())
            {
                // Enable bool
                bShouldPlaySound = true;

                // Set surface type
                CurrentSurfaceType = HitInfo.PhysMaterial.Get();

                // Set footstep location
                FootstepLocation = CalcFootstepLocation(Character);

                // Call the new function to play the sound based on surface type
                PlayFootstepSoundBySurfaceType(Character, GetSurfaceType(HitInfo));

                if (GetWorld())
                {
                    GetWorld()->GetTimerManager().SetTimer(FootstepTimerHandle, this, &UFootstepComponent::ResetFootstepTimer, FootstepDelay, false);
                }
            }
            else
            {
                // Invalid physical material; set the surface type to nullptr
                bShouldPlaySound = false;
                CurrentSurfaceType = nullptr;
            }
            // Debug message
            if (GEngine)
            {
                FString SurfaceTypeName = UEnum::GetValueAsString(TEXT("EPhysicalSurface"), GetSurfaceType(HitInfo));
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Surface Type: %s"), *SurfaceTypeName));
            }
		}
        else
        {
            // No hit; set the surface type to nullptr
            bShouldPlaySound = false;
            CurrentSurfaceType = nullptr;
        }
    }
    else
    {
        bShouldPlaySound = false;
        CurrentSurfaceType = nullptr;
    }

    
}

// New function to handle playing the sound based on the surface type
void UFootstepComponent::PlayFootstepSoundBySurfaceType(AActor* Character, EPhysicalSurface SurfaceType)
{
    switch (SurfaceType)
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
    default:
        // Handle any unknown or unsupported surface types if needed
        break;
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

float UFootstepComponent::DetermineFootstepOffset(ECharacterMovementState MovementState)
{
    if (!CachedCharacter)
    {
        UE_LOG(LogTemp, Error, TEXT("DetermineFootstepOffset: CachedCharacter is null"));
        return 0.f;
    }

    UE_LOG(LogTemp, Warning, TEXT("Current Movement State: %d"), (uint8)MovementState);

    switch (MovementState)
    {
    case ECharacterMovementState::ECMS_Walking:
        return .6f;
    case ECharacterMovementState::ECMS_Crouching:
        return 1.f;
    case ECharacterMovementState::ECMS_Sprinting:
        return .4f;
    case ECharacterMovementState::ECMS_Prone:
        return 1.4f;
    case ECharacterMovementState::ECMS_Jumping:
        return 0.f;
    case ECharacterMovementState::ECMS_Aiming:
        return 1.5f;
    default:
        return 0.f;
    }
}