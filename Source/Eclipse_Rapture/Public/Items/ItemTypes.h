#pragma once

UENUM(BlueprintType)
enum class EItemType : uint8
{
	EIT_Consumable UMETA(DisplayName = "Consumable"),
	EIT_Pickup UMETA(DisplayName = "Pickup"),
	EIT_Interactable UMETA(DisplayName = "Interactable"),
	EIT_Weapon UMETA(DisplayName = "Weapon")
};