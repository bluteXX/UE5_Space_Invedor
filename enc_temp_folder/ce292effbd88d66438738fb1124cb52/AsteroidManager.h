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

	AAsteroidManager();
	UFUNCTION(BlueprintCallable, Category = "Difficulty")
	void IncreaseDifficulty();
protected:

	virtual void BeginPlay() override;

	void SpawnAsteroid();
	void ScheduleNextSpawn();

	

	UPROPERTY(EditAnywhere, Category = "Difficulty")
	float SpawnIntervalReductionPerWave = 0.3f;

	UPROPERTY(EditAnywhere, Category = "Difficulty")
	float MinSpawnIntervalFloor = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<AAsteroid> AsteroidClass;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float MinSpawnInterval = 3.0f;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float MaxSpawnInterval = 7.0f;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float AsteroidSpeed = 150.0f;

private:

	FTimerHandle SpawnTimerHandle;
};