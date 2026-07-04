#include "AsteroidManager.h"
#include "Asteroid.h"
#include "GameTypes.h"

AAsteroidManager::AAsteroidManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AAsteroidManager::BeginPlay()
{
	Super::BeginPlay();
	ScheduleNextSpawn();
}

void AAsteroidManager::ScheduleNextSpawn()
{
	float Delay = FMath::FRandRange(MinSpawnInterval, MaxSpawnInterval);
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AAsteroidManager::SpawnAsteroid, Delay, false);
}
void AAsteroidManager::IncreaseDifficulty()
{
	MinSpawnInterval = FMath::Max(MinSpawnInterval - SpawnIntervalReductionPerWave, MinSpawnIntervalFloor);
	MaxSpawnInterval = FMath::Max(MaxSpawnInterval - SpawnIntervalReductionPerWave, MinSpawnIntervalFloor + 0.5f);
}

void AAsteroidManager::SpawnAsteroid()
{
	if (AsteroidClass && GetWorld())
	{
		
		int32 Edge = FMath::RandRange(0, 3);
		FVector SpawnLocation = FVector::ZeroVector;
		FVector2D Direction = FVector2D::ZeroVector;

		switch (Edge)
		{
		case 0: 
			SpawnLocation = FVector(PLAY_FIELD_MIN_X, 0.f, FMath::FRandRange(PLAY_FIELD_MIN_Z, PLAY_FIELD_MAX_Z));
			Direction = FVector2D(1.f, FMath::FRandRange(-0.5f, 0.5f));
			break;
		case 1: 
			SpawnLocation = FVector(PLAY_FIELD_MAX_X, 0.f, FMath::FRandRange(PLAY_FIELD_MIN_Z, PLAY_FIELD_MAX_Z));
			Direction = FVector2D(-1.f, FMath::FRandRange(-0.5f, 0.5f));
			break;
		case 2:
			SpawnLocation = FVector(FMath::FRandRange(PLAY_FIELD_MIN_X, PLAY_FIELD_MAX_X), 0.f, PLAY_FIELD_MAX_Z);
			Direction = FVector2D(FMath::FRandRange(-0.5f, 0.5f), -1.f);
			break;
		case 3: 
		default:
			SpawnLocation = FVector(FMath::FRandRange(PLAY_FIELD_MIN_X, PLAY_FIELD_MAX_X), 0.f, PLAY_FIELD_MIN_Z);
			Direction = FVector2D(FMath::FRandRange(-0.5f, 0.5f), 1.f);
			break;
		}

		AAsteroid* NewAsteroid = GetWorld()->SpawnActor<AAsteroid>(AsteroidClass, SpawnLocation, FRotator::ZeroRotator);
		if (NewAsteroid)
		{
			NewAsteroid->InitAsteroid(Direction, AsteroidSpeed, EAsteroidSize::Large);
		}
	}

	ScheduleNextSpawn();
}