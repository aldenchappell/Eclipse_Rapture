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

UENUM(BlueprintType)
enum class ECharacterMovementState : uint8
{
	ECMS_Idle UMETA(DisplayName = "Idle"),
	ECMS_Walking UMETA(DisplayName = "Walking"),
	ECMS_Sprinting UMETA(DisplayName = "Sprinting"),
	ECMS_Crouching UMETA(DisplayName = "Crouching"),
	ECMS_Prone UMETA(DisplayName = "Prone"),
	ECMS_Jumping UMETA(DisplayName = "Jumping")
};


