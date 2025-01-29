#pragma once

UENUM(BlueprintType)
enum class EBulletImpactTypes : uint8
{
	ABIT_None UMETA(DisplayName = "None"),
	ABIT_Flesh UMETA(DisplayName = "Flesh"),
	ABIT_Wood UMETA(DisplayName = "Wood"),
	ABIT_Metal UMETA(DisplayName = "Metal"),
	ABIT_Stone UMETA(DisplayName = "Stone"),
	ABIT_Glass UMETA(DisplayName = "Glass"),
	ABIT_Concrete UMETA(DisplayName = "Concrete"),
	ABIT_Dirt UMETA(DisplayName = "Dirt"),
	ABIT_Grass UMETA(DisplayName = "Grass"),
	ABIT_Water UMETA(DisplayName = "Water"),
	ABIT_Sand UMETA(DisplayName = "Sand"),
	ABIT_Snow UMETA(DisplayName = "Snow"),
	ABIT_Ice UMETA(DisplayName = "Ice")
};


