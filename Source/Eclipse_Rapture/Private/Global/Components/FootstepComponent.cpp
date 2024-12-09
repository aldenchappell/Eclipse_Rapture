
#include "Global/Components/FootstepComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Character/EclipseRaptureCharacter.h"

#define FootstepChannel ECollisionChannel::ECC_GameTraceChannel2

UFootstepComponent::UFootstepComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	FootstepDelay = .6f;
	FootstepVolumeMultiplier = 1.f;
	FootstepPitchMultiplier = 1.f;
	FootstepZOffset = 50.f;
	FootstepTraceDistance = 100.f;
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
            // Debug: Playing the footstep sound
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Playing footstep sound"));
            }

            UGameplayStatics::PlaySoundAtLocation(
                GetWorld(),
                RandomFootstepSound,
                CalcFootstepLocation(Character),
                FootstepVolumeMultiplier,
                FootstepPitchMultiplier);

            ResetFootstepTimer();
        }
        else
        {
            // Debug: bShouldPlaySound is false or no valid sound
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Sound not played: either bShouldPlaySound is false or no valid sound found"));
            }
        }
    }
    else
    {
        // Debug: No footstep sounds available
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("No footstep sounds available"));
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

        // Debug: Display trace start and end locations
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, FString::Printf(TEXT("Tracing from: %s to: %s"), *TraceStart.ToString(), *TraceEnd.ToString()));
        }

        // Draw the debug line for the trace
        DrawDebugLine(
            GetWorld(),
            TraceStart,
            TraceEnd,
            FColor::Blue,    // Line color (you can change this to whatever color you prefer)
            false,           // Persistent (false means the line will disappear after a short time)
            1.0f,            // Lifetime (1 second in this case)
            0,               // Depth priority (0 is fine for most cases)
            2.0f             // Line thickness
        );

        if (GetWorld()->LineTraceSingleByChannel(
            HitInfo,
            TraceStart,
            TraceEnd,
            FootstepChannel))
        {
            // Check if the hit has a valid physical material
            if (HitInfo.PhysMaterial->SurfaceType)
            {
                // Enable sound to play
                bShouldPlaySound = true;

                // Set surface type and footstep location
                CurrentSurfaceType = HitInfo.PhysMaterial.Get();
                FootstepLocation = CalcFootstepLocation(Character);

                // Debug: Show the hit location, actor name, and surface type
                if (GEngine)
                {
                    FString ActorName = HitInfo.GetActor() ? HitInfo.GetActor()->GetName() : "No Actor";
                    FString SurfaceTypeName = UEnum::GetValueAsString(TEXT("EPhysicalSurface"), GetSurfaceType(HitInfo));
                    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("Hit Actor: %s, Hit Location: %s, Surface Type: %s"), *ActorName, *HitInfo.Location.ToString(), *SurfaceTypeName));
                }

                // Play sound based on surface type
                PlayFootstepSoundBySurfaceType(Character, GetSurfaceType(HitInfo));

                // Start/reset the footstep timer
                if (GetWorld())
                {
                    GetWorld()->GetTimerManager().SetTimer(FootstepTimerHandle, this, &UFootstepComponent::ResetFootstepTimer, FootstepDelay, false);
                }
            }
            else
            {
                // Debug: No valid physical material
                if (GEngine)
                {
                    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("No valid physical material detected!"));
                }

                bShouldPlaySound = false;
                CurrentSurfaceType = nullptr;
            }
        }
        else
        {
            // Debug: No hit detected
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("No hit detected!"));
            }

            bShouldPlaySound = false;
            CurrentSurfaceType = nullptr;
        }
    }
    else
    {
        // Debug: Character reference is null
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Character reference is null!"));
        }

        bShouldPlaySound = false;
        CurrentSurfaceType = nullptr;
    }
}



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