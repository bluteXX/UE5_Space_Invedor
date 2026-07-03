#pragma once

#include "CoreMinimal.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"

class AEnemyShip;
class ASpiralEnemy;

UCLASS()
class SPACE_INVADER_API AEnemyManager : public AActor
{
	GENERATED_BODY()



protected:

	virtual void BeginPlay() override;


public:


	// Enemy Management

	AEnemyManager();

	void SpawnWave();
	void SpawnSpiralEnemy();

	// Removes a destroyed enemy from the manager.
	void RemoveEnemy(AEnemyShip* Enemy);
	void RemoveSpiralEnemy(ASpiralEnemy* Enemy);

	AEnemyShip* GetRandomEnemyInOrbit(int32 OrbitIndex);

	// Fires from a random enemy on the lowest active orbit.
	void EnemyShootFromLowestOrbit();


protected:


	// Spawn Settings

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<ASpiralEnemy> SpiralEnemyClass;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float SpiralEnemyTimeToCenter = 180.0f;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	int32 NumberOfSpiralEnemies = 1;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<AEnemyShip> EnemyClassToSpawn;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	int32 NumberOfOrbits = 11;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	int32 EnemiesPerOrbit = 5;

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


	void ScheduleNextShot();
	void CheckForWin();
	int32 GetLowestActiveOrbitIndex() const;


	// Runtime Data


	// Enemies grouped by orbit ring.
	TArray<TArray<AEnemyShip*>> EnemyOrbits;

	// Flat list of all active enemies.
	TArray<AEnemyShip*> ActiveEnemies;

	TArray<ASpiralEnemy*> ActiveSpiralEnemies;

	FTimerHandle ShootTimerHandle;
};