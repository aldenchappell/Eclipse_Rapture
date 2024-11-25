#pragma once

UENUM(BlueprintType)
enum class EDamageType : uint8
{
    EDT_Melee UMETA(DisplayName = "Melee"),
    EDT_Bullet UMETA(DisplayName = "Bullet"),
    EDT_Explosion UMETA(DisplayName = "Explosion"),
	EDT_Environment UMETA(DisplayName = "Environment")
};

UENUM(BlueprintType)
enum class EDamageResponse : uint8
{
	EDR_None UMETA(DisplayName = "None"),
	EDR_HitReaction UMETA(DisplayName = "Hit Reaction"),
	EDR_Stagger UMETA(DisplayName = "Stagger"),
	EDR_Stun UMETA(DisplayName = "Stun"),
	EDR_Knockback UMETA(DisplayName = "Knockback")
};