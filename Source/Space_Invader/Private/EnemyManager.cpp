#include "EnemyManager.h"
#include "EnemyShip.h"
#include "Engine/World.h"
#include "SpiralEnemy.h"
#include "GameTypes.h"
#include "SpaceInvaderNormal.h"
#include "Kismet/GameplayStatics.h"
#include "SpaceInvaderGameState.h"

// ==================== Lifecycle ====================

AEnemyManager::AEnemyManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	ScheduleNextShot();
	SpawnWave();
	SpawnSpiralEnemy();
}

// ==================== Gameplay Functions ====================

void AEnemyManager::SpawnWave()
{
	if (!EnemyClassToSpawn) return;

	EnemyOrbits.Empty();
	EnemyOrbits.SetNum(NumberOfOrbits);

	ActiveEnemies.Empty();

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	float AngleStep = 360.0f / EnemiesPerOrbit;

	for (int32 Orbit = 0; Orbit < NumberOfOrbits; Orbit++)
	{
		float CurrentRadius = StartingRadius + Orbit * RadiusStep;

		bool bIsOffsetOrbit = (Orbit % 2 == 1);
		float AngleOffset = bIsOffsetOrbit ? (AngleStep * 0.5f) : 0.0f;

		for (int32 i = 0; i < EnemiesPerOrbit; i++)
		{
			float CurrentAngle = i * AngleStep + AngleOffset;

			AEnemyShip* NewEnemy =
				GetWorld()->SpawnActor<AEnemyShip>(
					EnemyClassToSpawn,
					FVector::ZeroVector,
					FRotator::ZeroRotator,
					SpawnParams);

			if (NewEnemy)
			{
				NewEnemy->SetupOrbit(CurrentRadius, CurrentAngle);
				NewEnemy->SetManager(this);
				NewEnemy->SetDescendStep(RadiusStep);
				NewEnemy->ApplySpeedMultiplier(CurrentSpeedMultiplier);
				EnemyOrbits[Orbit].Add(NewEnemy);
				ActiveEnemies.Add(NewEnemy);
			}
		}
	}
}

void AEnemyManager::SpawnSpiralEnemy()
{
	if (!SpiralEnemyClass || !GetWorld()) return;

	for (int32 i = 0; i < NumberOfSpiralEnemies; i++)
	{
		int32 Edge = FMath::RandRange(0, 3);
		FVector SpawnLocation = FVector::ZeroVector;

		switch (Edge)
		{
		case 0: SpawnLocation = FVector(PLAY_FIELD_MIN_X, 0.f, FMath::FRandRange(PLAY_FIELD_MIN_Z, PLAY_FIELD_MAX_Z)); break;
		case 1: SpawnLocation = FVector(PLAY_FIELD_MAX_X, 0.f, FMath::FRandRange(PLAY_FIELD_MIN_Z, PLAY_FIELD_MAX_Z)); break;
		case 2: SpawnLocation = FVector(FMath::FRandRange(PLAY_FIELD_MIN_X, PLAY_FIELD_MAX_X), 0.f, PLAY_FIELD_MAX_Z); break;
		case 3: SpawnLocation = FVector(FMath::FRandRange(PLAY_FIELD_MIN_X, PLAY_FIELD_MAX_X), 0.f, PLAY_FIELD_MIN_Z); break;
		}

		ASpiralEnemy* NewEnemy = GetWorld()->SpawnActor<ASpiralEnemy>(SpiralEnemyClass, SpawnLocation, FRotator::ZeroRotator);
		if (NewEnemy)
		{
			NewEnemy->SetupSpiral(SpawnLocation, SpiralEnemyTimeToCenter);
			NewEnemy->SetManager(this);
			ActiveSpiralEnemies.Add(NewEnemy);
		}
	}
}

void AEnemyManager::RemoveEnemy(AEnemyShip* Enemy)
{
	if (!Enemy) return;

	ActiveEnemies.Remove(Enemy);

	for (int32 Orbit = 0; Orbit < EnemyOrbits.Num(); Orbit++)
	{
		EnemyOrbits[Orbit].Remove(Enemy);
	}

	ASpaceInvaderGameState* GS = GetWorld()->GetGameState<ASpaceInvaderGameState>();
	if (GS)
	{
		GS->AddKill();
	}

	CheckForWin();
}

void AEnemyManager::RemoveSpiralEnemy(ASpiralEnemy* Enemy)
{
	if (!Enemy) return;

	ActiveSpiralEnemies.Remove(Enemy);

	ASpaceInvaderGameState* GS = GetWorld()->GetGameState<ASpaceInvaderGameState>();
	if (GS)
	{
		GS->AddKill();
	}

	CheckForWin();
}

AEnemyShip* AEnemyManager::GetRandomEnemyInOrbit(int32 OrbitIndex)
{
	if (!EnemyOrbits.IsValidIndex(OrbitIndex)) return nullptr;

	TArray<AEnemyShip*>& Orbit = EnemyOrbits[OrbitIndex];

	TArray<AEnemyShip*> ValidEnemies;
	for (AEnemyShip* Enemy : Orbit)
	{
		if (IsValid(Enemy))
		{
			ValidEnemies.Add(Enemy);
		}
	}

	if (ValidEnemies.Num() == 0) return nullptr;

	int32 RandomIndex = FMath::RandRange(0, ValidEnemies.Num() - 1);
	return ValidEnemies[RandomIndex];
}

void AEnemyManager::EnemyShootFromLowestOrbit()
{
	if (ActiveEnemies.Num() > 0 && FMath::FRand() <= ChanceToFire)
	{
		int32 LowestOrbit = GetLowestActiveOrbitIndex();

		if (LowestOrbit != INDEX_NONE)
		{
			AEnemyShip* Shooter = GetRandomEnemyInOrbit(LowestOrbit);
			if (Shooter)
			{
				Shooter->TryShoot();
			}

			if (FMath::FRand() <= ChanceForExtraShot)
			{
				AEnemyShip* ExtraShooter = GetRandomEnemyInOrbit(LowestOrbit);
				if (ExtraShooter && ExtraShooter != Shooter)
				{
					ExtraShooter->TryShoot();
				}
			}
		}
	}

	ScheduleNextShot();
}

void AEnemyManager::IncreaseDifficulty()
{
	CurrentSpeedMultiplier *= SpeedMultiplierPerWave;
	EnemiesPerOrbit += ExtraEnemiesPerWave;
	EnemiesPerOrbit += 1;
	MinFireInterval = FMath::Max(MinFireInterval - FireIntervalReductionPerWave, MinFireIntervalFloor);
	MaxFireInterval = FMath::Max(MaxFireInterval - FireIntervalReductionPerWave, MinFireIntervalFloor + 0.3f);
}

// ==================== Internal Functions ====================

void AEnemyManager::ScheduleNextShot()
{
	float NextInterval = FMath::FRandRange(MinFireInterval, MaxFireInterval);

	GetWorldTimerManager().SetTimer(
		ShootTimerHandle,
		this,
		&AEnemyManager::EnemyShootFromLowestOrbit,
		NextInterval,
		false
	);
}

int32 AEnemyManager::GetLowestActiveOrbitIndex() const
{
	for (int32 Orbit = 0; Orbit < EnemyOrbits.Num(); Orbit++)
	{
		for (AEnemyShip* Enemy : EnemyOrbits[Orbit])
		{
			if (IsValid(Enemy))
			{
				return Orbit;
			}
		}
	}

	return INDEX_NONE;
}

void AEnemyManager::CheckForWin()
{
	if (ActiveEnemies.Num() == 0 && ActiveSpiralEnemies.Num() == 0)
	{
		OnAllEnemiesDefeated.Broadcast();
	}
}