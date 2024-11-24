#pragma once

UENUM(BlueprintType)
enum class EDamageType : uint8
{
    EDT_Melee UMETA(DisplayName = "Melee"),
    EDT_Bullet UMETA(DisplayName = "Bullet"),
    EDT_Explosion UMETA(DisplayName = "Explosion")
};