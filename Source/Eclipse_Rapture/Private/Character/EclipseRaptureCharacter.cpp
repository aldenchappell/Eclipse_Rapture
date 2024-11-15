

#include "Character/EclipseRaptureCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapons/WeaponBase.h"
#include "UI/AmmoCounterWComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/WidgetEclipseRaptureCharacter.h"
#include "Components/Image.h" 
#include "Kismet/KismetMathLibrary.h"
#include "Global/Components/HealthComponent.h"
#include "Character/InventoryComponent.h"
#include "Items/Components/FlashlightComponent.h"
#include "Components/SpotLightComponent.h"
#include "Interfaces/Unlockable.h"


AEclipseRaptureCharacter::AEclipseRaptureCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    //Setup collision capsule
    GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

    //Setup movement speeds
    WalkMovementSpeed = 450.f;
    StoredWalkSpeed = WalkMovementSpeed;
    SprintMovementSpeed = StoredWalkSpeed * 1.5f;
    StoredSprintSpeed = SprintMovementSpeed;
    GetCharacterMovement()->MaxWalkSpeedCrouched = 150.f;
    ProneMovementSpeed = 100.f;
    GetCharacterMovement()->MaxWalkSpeed = StoredWalkSpeed;

    //Setup player mesh
    GetMesh()->SetOnlyOwnerSee(true);
    GetMesh()->SetupAttachment(GetRootComponent());
    GetMesh()->bCastDynamicShadow = false;
    GetMesh()->CastShadow = false;
    GetMesh()->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
    GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

    //Setup crouching
    CrouchEyeOffset = FVector(0.f);
    CrouchEntranceSpeed = 12.f;

    //Setup proning
    ProneEyeOffset = FVector(0.f);
    ProneEntranceSpeed = 2.f;
    ProneEyeHeightZ = -50.f;

    bIsAiming = false;

	//setup health component
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

    //setup inventory component
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory Component"));
	InventoryComponent->Capacity = 20;

    CharacterType = ECharacterType::ECT_Player;
}

void AEclipseRaptureCharacter::BeginPlay()
{
    Super::BeginPlay();

    GetCharacterMovement()->MaxWalkSpeed = StoredWalkSpeed;
}

void AEclipseRaptureCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AEclipseRaptureCharacter::HandleCrouch(float DeltaTime)
{
    //Handle crouching interpolation
    float CrouchInterpTime = FMath::Min(1.f, CrouchEntranceSpeed * DeltaTime);
    CrouchEyeOffset = (1.f - CrouchInterpTime) * CrouchEyeOffset;
}



void AEclipseRaptureCharacter::DoMantleTrace(
    float TraceLength, float TraceZOffset, float FallHeightAdjust,
    FVector& MantlePos1, FVector& MantlePos2)
{
    bCanMantle = false;
    //start the trace around eye level(ish)
    FVector TraceStart = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 50.f);
    FVector TraceEnd = TraceStart + GetActorForwardVector() * TraceLength;

    TArray<AActor*> ActorsToIgnore;
    ActorsToIgnore.Add(this);

    FHitResult InitialHitInfo, SecondaryHitInfo, TertiaryHitInfo, QuaternaryHitInfo;

    // Line Trace to detect object in front of player
    if (UKismetSystemLibrary::LineTraceSingle(
        GetWorld(), TraceStart, TraceEnd, ETraceTypeQuery::TraceTypeQuery1,
        false, ActorsToIgnore, EDrawDebugTrace::None, InitialHitInfo, true, FLinearColor::Black))
    {
        // Adjust Z offset based on whether player is falling
        bool IsFalling = GetCharacterMovement()->IsFalling();
        FVector SphereTraceEnd = InitialHitInfo.Location;
        SphereTraceEnd.Z += IsFalling ? FallHeightAdjust : TraceZOffset;

        //Sphere Trace to determine mantle height
        if (UKismetSystemLibrary::SphereTraceSingle(
            GetWorld(), InitialHitInfo.Location, SphereTraceEnd, 10.f,
            ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore,
            EDrawDebugTrace::ForDuration, SecondaryHitInfo, true, FLinearColor::Gray))
        {
            //Calculate mantle positions
            MantlePos1 = SecondaryHitInfo.ImpactPoint + GetActorForwardVector() * -50.f; //-50
            MantlePos2 = SecondaryHitInfo.ImpactPoint + GetActorForwardVector() * 120.f; //120
            bCanMantle = true;

            //Perform Tertiary Sphere Trace to check for clear space
            FVector TertiaryTraceLocation = MantlePos2 + FVector(0.f, 0.f, 20.f);
            if (UKismetSystemLibrary::SphereTraceSingle(
                GetWorld(), TertiaryTraceLocation, TertiaryTraceLocation, 10.f,
                ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore,
                EDrawDebugTrace::ForDuration, TertiaryHitInfo, true))
            {
                bCanMantle = false;

                // Validate Mantle Positions
                if ((MantlePos1 == FVector::ZeroVector) || (MantlePos2 == FVector::ZeroVector))
                {
                    bCanMantle = false;
                }
                else
                {
                    // Adjust MantlePos2 based on Tertiary Trace
                    MantlePos2 = TertiaryHitInfo.ImpactPoint + GetActorForwardVector() * 25.f; //50

                    // Perform Final Quad Sphere Trace
                    FVector QuadTraceStart = MantlePos1;
                    FVector QuadTraceEnd = MantlePos2 + FVector(0.f, 0.f, 50.f); //100

                    if (UKismetSystemLibrary::SphereTraceSingle(
                        GetWorld(), QuadTraceStart, QuadTraceEnd, 20.f,
                        ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore,
                        EDrawDebugTrace::ForDuration, QuaternaryHitInfo, true))
                    {
                        bCanMantle = false;
                    }
                }
            }
            else
            {
                MantlePos2 = TertiaryHitInfo.ImpactPoint + GetActorForwardVector() * 25.f; //50
            }
        }
    }
    else
    {
        bCanMantle = false;
    }
}



