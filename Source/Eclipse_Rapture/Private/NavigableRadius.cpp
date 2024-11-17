#include "NavigableRadius.h"
#include "Components/SphereComponent.h"

UNavigableRadius::UNavigableRadius()
{
    PrimaryComponentTick.bCanEverTick = false;

    // Create the Sphere Component
    NavigableRadiusSphere = CreateDefaultSubobject<USphereComponent>(TEXT("NavigableRadiusSphere"));
    if (NavigableRadiusSphere)
    {

        // Attach the sphere to the owning actor's root component
        if (GetOwner())
        {
			NavigableRadiusSphere->SetupAttachment(GetOwner()->GetRootComponent());
			NavigableRadiusSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        }
    }
}
