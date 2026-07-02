
#pragma once

#include "CoreMinimal.h"
#include "GameTypes.generated.h"

UENUM(BlueprintType)
enum class ETeamID : uint8
{
	Player UMETA(DisplayName = "Player"),
	Enemy UMETA(DisplayName = "Enemy"),
	Neutral UMETA(DisplayName = "Neutral")
};