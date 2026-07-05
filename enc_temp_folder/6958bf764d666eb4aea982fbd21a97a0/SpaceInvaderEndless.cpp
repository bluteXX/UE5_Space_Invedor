#include "SpaceInvaderEndless.h"
#include "EnemyManager.h"
#include "AsteroidManager.h"
#include "Kismet/GameplayStatics.h"

void ASpaceInvaderEndless::BeginPlay()
{
	Super::BeginPlay();

	AActor* AsteroidManagerActor = UGameplayStatics::GetActorOfClass(this, AAsteroidManager::StaticClass());
	AsteroidManagerRef = Cast<AAsteroidManager>(AsteroidManagerActor);
}

void ASpaceInvaderEndless::HandleAllEnemiesDefeated()
{
	if (bIsGameOver)
	{
		return;
	}

	CurrentWave++;
	UE_LOG(LogTemp, Warning, TEXT("Endless: fala %d"), CurrentWave);

	if (EnemyManagerRef)
	{
		EnemyManagerRef->IncreaseDifficulty();
		EnemyManagerRef->SpawnWave();
		EnemyManagerRef->SpawnSpiralEnemy();
	}

	if (AsteroidManagerRef)
	{
		AsteroidManagerRef->IncreaseDifficulty();
	}
}