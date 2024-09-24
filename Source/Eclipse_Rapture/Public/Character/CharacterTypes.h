#pragma once

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_Unequipped UMETA(DisplayName = "Unequipped"),
	ECS_MeleeOnly UMETA(DisplayName = "Melee Only"),
	ECS_PistolEquipped UMETA(DisplayName = "Pistol Equipped"),
	ECS_RifleEquipped UMETA(DisplayName = "Rifle Equipped"),
	ECS_ShotgunEquipped UMETA(DisplayName = "Shotgun Equipped")
};


