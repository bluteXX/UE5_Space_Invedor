#pragma once

#include "CoreMinimal.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"
#include "AsteroidManager.generated.h"

class AAsteroid;

UCLASS()
class SPACE_INVADER_API AAsteroidManager : public AActor
{
	GENERATED_BODY()

public:

	// ==================== Lifecycle ====================

	AAsteroidManager();

	// ==================== Gameplay Functions ====================

	UFUNCTION(BlueprintCallable, Category = "Difficulty")
	void IncreaseDifficulty();

protected:

	virtual void BeginPlay() override;

	// ==================== Internal Logic ====================

	void SpawnAsteroid();
	void ScheduleNextSpawn();

	// ==================== Spawn Configuration ====================

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<AAsteroid> AsteroidClass;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float MinSpawnInterval = 3.0f;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float MaxSpawnInterval = 7.0f;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float AsteroidSpeed = 150.0f;

	// ==================== Difficulty Configuration ====================

	UPROPERTY(EditAnywhere, Category = "Difficulty")
	float SpawnIntervalReductionPerWave = 0.3f;

	UPROPERTY(EditAnywhere, Category = "Difficulty")
	float MinSpawnIntervalFloor = 0.5f;

private:

	// ==================== Runtime State ====================

	FTimerHandle SpawnTimerHandle;
};