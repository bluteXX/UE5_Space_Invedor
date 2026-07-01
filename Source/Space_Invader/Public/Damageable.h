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

// Interface class (no logic here)
class IDamageable
{
	GENERATED_BODY()

public:

	// Called when object receives damage
	UFUNCTION(BlueprintNativeEvent)
	void TakeHit(float Damage);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)

	ETeamID GetTeamID() const;
};