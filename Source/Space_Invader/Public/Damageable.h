#pragma once

#include "GameTypes.h"
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Damageable.generated.h"

UINTERFACE(MinimalAPI)
class UDamageable : public UInterface
{
	GENERATED_BODY()
};

class IDamageable
{
	GENERATED_BODY()

public:

	// ==================== Gameplay Functions ====================

	UFUNCTION(BlueprintNativeEvent)
	void TakeHit(float Damage);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	ETeamID GetTeamID() const;
};