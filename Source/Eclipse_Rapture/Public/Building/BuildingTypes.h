#pragma once

UENUM(BlueprintType)
enum class EUpgradeType : uint8
{
	EUT_Wood UMETA(DisplayName = "Wood"),
	EUT_Brick UMETA(DisplayName = "Brick"),
	EUT_Metal UMETA(DisplayName = "Sheet Metal"),
	EUT_Reinforced UMETA(DisplayName = "Reinforced Material")
};

UENUM(BlueprintType)
enum class EUpgradeCostType : uint8
{
	EUCT_Wood UMETA(DisplayName = "Wood"),
	EUCT_Brick UMETA(DisplayName = "Brick"),
	EUCT_Metal UMETA(DisplayName = "Sheet Metal"),
	EUCT_Reinforced UMETA(DisplayName = "Reinforced Material")
};