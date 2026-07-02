#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SpaceInvaderGameState.generated.h"

UCLASS(BlueprintType)
class SPACE_INVADER_API ASpaceInvaderGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ASpaceInvaderGameState();

	UPROPERTY(BlueprintReadOnly, Category = "Stats")
	int32 EnemiesKilled = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Stats")
	float GameTime = 0.0f;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void AddKill();

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void StopTimer();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	bool bTimerRunning = true;
};