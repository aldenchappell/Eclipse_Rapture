#pragma once

UENUM(BlueprintType)
enum class EBuildingType : uint8
{
	EBT_Wall UMETA(DisplayName = "Wall"),
	EBT_Floor UMETA(DisplayName = "Floor"),
	EBT_Stairs UMETA(DisplayName = "Stairs"),
	EBT_Roof UMETA(DisplayName = "Roof"),
	EBT_Door UMETA(DisplayName = "Door"),
	EBT_Window UMETA(DisplayName = "Window"),
	EBT_Foundation UMETA(DisplayName = "Foundation")
};

UENUM(BlueprintType)
enum class EUpgradeType : uint8
{
	EUT_None UMETA(DisplayName = "None"),
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