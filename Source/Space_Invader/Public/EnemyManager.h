#pragma once

#include "CoreMinimal.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"

class AEnemyShip;

UCLASS()
class SPACE_INVADER_API AEnemyManager : public AActor
{
	GENERATED_BODY()

public:

	
	// Constructor & Lifecycle
	

	AEnemyManager();

protected:

	virtual void BeginPlay() override;


public:

	
	// Enemy Management
	

	
	void SpawnWave();

	// Removes a destroyed enemy from the manager.
	void RemoveEnemy(AEnemyShip* Enemy);

	
	AEnemyShip* GetLowestEnemyInColumn(int32 Column);

	// Chooses a random column and attempts to fire.
	void EnemyShootRandomColumn();


protected:

	
	// Spawn Settings
	

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<AEnemyShip> EnemyClassToSpawn;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	int32 EnemiesPerColumn = 5;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	int32 NumberOfColumns = 11;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float StartingRadius = 5000.f;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float RadiusStep = 100.f;


	
	// Shooting Settings
	

	UPROPERTY(EditAnywhere, Category = "Shooting")
	float MinFireInterval = 0.4f;

	UPROPERTY(EditAnywhere, Category = "Shooting")
	float MaxFireInterval = 1.2f;

	UPROPERTY(EditAnywhere, Category = "Shooting")
	float ChanceToFire = 0.6f;

	UPROPERTY(EditAnywhere, Category = "Shooting")
	float ChanceForExtraShot = 0.2f;


private:

	
	// Internal Functions
	

	// Schedules the next enemy shot.
	void ScheduleNextShot();


	
	// Runtime Data
	

	// Enemies grouped by columns.
	TArray<TArray<AEnemyShip*>> EnemyColumns;

	// Flat list of all active enemies.
	TArray<AEnemyShip*> ActiveEnemies;

	
	FTimerHandle ShootTimerHandle;
};