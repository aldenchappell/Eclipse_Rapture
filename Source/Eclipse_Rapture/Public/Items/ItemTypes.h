#pragma once

UENUM(BlueprintType)
enum class EItemType : uint8
{
	EIT_Consumable UMETA(DisplayName = "Consumable"),
	EIT_Pickup UMETA(DisplayName = "Pickup"),
	EIT_Interactable UMETA(DisplayName = "Interactable"),
	EIT_Weapon UMETA(DisplayName = "Weapon"),
	EIT_Clothing UMETA(DisplayName = "Clothing")
};

UENUM(BlueprintType)
enum class EUsecaseType : uint8
{
	EUT_None UMETA(DisplayName = "None"),
	EUT_Ammo UMETA(DisplayName = "Ammo"),
	EUT_Healing UMETA(DisplayName = "Health"),
	EUT_Thirst UMETA(DisplayName = "Thirst"),
	EUT_Hunger UMETA(DisplayName = "Hunger"),
	EUT_Weapon UMETA(DisplayName = "Weapon"),
	EUT_Clothing UMETA(DisplayName = "Clothing")
};

UENUM(BlueprintType)
enum class EUseImpactType : uint8
{
	EUT_None UMETA(DisplayName = "None"),
	EUT_Low UMETA(DisplayName = "Low"),
	EUT_Medium UMETA(DisplayName = "Medium"),
	EUT_High UMETA(DisplayName = "High")
};

UENUM(BlueprintType)
enum class EMainItemUseDescriptionType : uint8
{
	EMDT_None UMETA(DisplayName = "None"),
	EMDT_Health UMETA(DisplayName = "Health Restoration"),
};

UENUM(BlueprintType)
enum class ESecondaryItemUseDescriptionType : uint8
{
	EMDT_None UMETA(DisplayName = "None"),
	EMDT_Bleeding UMETA(DisplayName = "Reduce Bleeding")
};