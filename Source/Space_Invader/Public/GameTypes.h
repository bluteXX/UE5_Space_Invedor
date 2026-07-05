#pragma once

#include "CoreMinimal.h"
#include "GameTypes.generated.h"

// ==================== Enums ====================

UENUM(BlueprintType)
enum class ETeamID : uint8
{
	Player  UMETA(DisplayName = "Player"),
	Enemy   UMETA(DisplayName = "Enemy"),
	Neutral UMETA(DisplayName = "Neutral")
};

UENUM(BlueprintType)
enum class EAsteroidSize : uint8
{
	Large  UMETA(DisplayName = "Large"),
	Medium UMETA(DisplayName = "Medium"),
	Small  UMETA(DisplayName = "Small")
};

// ==================== Gameplay Constants ====================

constexpr float PLAYER_ORBIT_RADIUS = 2000.0f;
constexpr float DEFEAT_ORBIT_RADIUS = 3000.0f;

constexpr float PLAY_FIELD_MIN_X = -20000.0f;
constexpr float PLAY_FIELD_MAX_X = 20000.0f;

constexpr float PLAY_FIELD_MIN_Z = -11250.0f;
constexpr float PLAY_FIELD_MAX_Z = 11250.0f;