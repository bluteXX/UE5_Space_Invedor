#include "SpaceInvaderGameState.h"

ASpaceInvaderGameState::ASpaceInvaderGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASpaceInvaderGameState::BeginPlay()
{
	Super::BeginPlay();
	GameTime = 0.0f;
	EnemiesKilled = 0;
	bTimerRunning = true;
}

void ASpaceInvaderGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bTimerRunning)
	{
		GameTime += DeltaTime;
	}
}

void ASpaceInvaderGameState::AddKill()
{
	EnemiesKilled++;
}

void ASpaceInvaderGameState::StopTimer()
{
	bTimerRunning = false;
}