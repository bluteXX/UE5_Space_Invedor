#include "EnemyManager.h"
#include "EnemyShip.h"
#include "Engine/World.h"

AEnemyManager::AEnemyManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	ScheduleNextShot();
	SpawnWave();
}

void AEnemyManager::ScheduleNextShot()
{
	float NextInterval = FMath::FRandRange(MinFireInterval, MaxFireInterval);

	GetWorldTimerManager().SetTimer(
		ShootTimerHandle,
		this,
		&AEnemyManager::EnemyShootRandomColumn,
		NextInterval,
		false 
	);
}
void AEnemyManager::EnemyShootRandomColumn()
{
	if (ActiveEnemies.Num() > 0 && FMath::FRand() <= ChanceToFire)
	{
		int32 RandomCol = FMath::RandRange(0, NumberOfColumns - 1);
		AEnemyShip* Shooter = GetLowestEnemyInColumn(RandomCol);
		if (Shooter)
		{
			Shooter->TryShoot();
		}

		
		if (FMath::FRand() <= ChanceForExtraShot)
		{
			int32 ExtraCol = FMath::RandRange(0, NumberOfColumns - 1);
			AEnemyShip* ExtraShooter = GetLowestEnemyInColumn(ExtraCol);
			if (ExtraShooter && ExtraShooter != Shooter)
			{
				ExtraShooter->TryShoot();
			}
		}
	}

	
	ScheduleNextShot();
}

void AEnemyManager::SpawnWave()
{
	if (!EnemyClassToSpawn) return;

	EnemyColumns.Empty();
	EnemyColumns.SetNum(NumberOfColumns);

	ActiveEnemies.Empty();

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	float AngleStep = 360.0f / NumberOfColumns;

	for (int32 Col = 0; Col < NumberOfColumns; Col++)
	{
		float BaseAngle = Col * AngleStep;

		for (int32 Row = 0; Row < EnemiesPerColumn; Row++)
		{
			float CurrentRadius = StartingRadius + Row * RadiusStep;

			AEnemyShip* NewEnemy =
				GetWorld()->SpawnActor<AEnemyShip>(
					EnemyClassToSpawn,
					FVector::ZeroVector,
					FRotator::ZeroRotator,
					SpawnParams);

			if (NewEnemy)
			{
				NewEnemy->SetupOrbit(CurrentRadius, BaseAngle);
				NewEnemy->SetManager(this);
				NewEnemy->SetDescendStep(RadiusStep);
				EnemyColumns[Col].Add(NewEnemy);
				ActiveEnemies.Add(NewEnemy);
			}
		}
	}
}

void AEnemyManager::RemoveEnemy(AEnemyShip* Enemy)
{
	if (!Enemy) return;

	
	ActiveEnemies.Remove(Enemy);

	for (int32 Col = 0; Col < EnemyColumns.Num(); Col++)
	{
		
		EnemyColumns[Col].Remove(Enemy);
	}
}

AEnemyShip* AEnemyManager::GetLowestEnemyInColumn(int32 Column)
{
	if (!EnemyColumns.IsValidIndex(Column)) return nullptr;

	TArray<AEnemyShip*>& Col = EnemyColumns[Column];

	for (int32 i = 0; i < Col.Num(); i++)
	{
		if (IsValid(Col[i]))
		{
			return Col[i];
		}
	}

	return nullptr;
}