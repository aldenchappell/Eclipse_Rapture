// DespawningComponent.cpp

#include "Enemies/DespawningComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


UDespawningComponent::UDespawningComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

    // Initialize and set up DespawnSphere
    DespawnSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DespawnSphere"));
    DespawnSphere->SetSphereRadius(DespawnRadius);
}

void UDespawningComponent::BeginPlay()
{
    Super::BeginPlay();

    // Register overlap events
    DespawnSphere->OnComponentBeginOverlap.AddDynamic(this, &UDespawningComponent::OnSphereOverlap);
    DespawnSphere->OnComponentEndOverlap.AddDynamic(this, &UDespawningComponent::OnSphereEndOverlap);
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
        CheckDespawn();
    }
}

void UDespawningComponent::StartDespawnTimer()
{
    // Start the timer-based despawn only after character death only if despawn radius isn't enabled.
    if (!bEnableDespawnRadius)
    {
        GetWorld()->GetTimerManager().SetTimer(
            DespawnTimerHandle,
            this,
            &UDespawningComponent::CheckDespawn,
            DespawnDelay,
            false);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Despawn timer not started. Despawn radius is enabled."));
    }
}

void UDespawningComponent::CheckDespawn()
{
    if (bEnableDespawnRadius)
    {
        // If using radius-based despawning, check player distance
        if (APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
        {
            float DistanceToPlayer = FVector::Dist(GetOwner()->GetActorLocation(), PlayerPawn->GetActorLocation());

            if (DistanceToPlayer > DespawnSphere->GetScaledSphereRadius())
            {
                GetOwner()->Destroy();
            }
        }
    }
    else
    {
        // Timer-based despawn
        GetOwner()->Destroy();
    }
}
