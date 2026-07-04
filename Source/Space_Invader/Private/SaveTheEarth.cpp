#include "SaveTheEarth.h"
#include "GameFramework/PlayerController.h"
#include "EnemyManager.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Planet.h"
ASaveTheEarth::ASaveTheEarth()
{}

void ASaveTheEarth::OnPlayerDied()
{
	UE_LOG(LogTemp, Warning, TEXT("Gracz"), RespawnDelay);

	

	if (bIsGameOver)
	{
		return;
	}

	GetWorldTimerManager().SetTimer(
		RespawnTimerHandle,
		this,
		&ASaveTheEarth::RespawnPlayer,
		RespawnDelay,
		false);
}

void ASaveTheEarth::RespawnPlayer()
{
	if (bIsGameOver)
	{
		return;
	}

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC)
	{
		return;
	}

	
	RestartPlayer(PC);

	
	BindPlayerHealthDelegate(PC->GetPawn());
}

void ASaveTheEarth::HandleAllEnemiesDefeated()
{
	if (bIsGameOver)
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Next Wave"));

	if (EnemyManagerRef)
	{
		EnemyManagerRef->SpawnWave();
		EnemyManagerRef->SpawnSpiralEnemy();
	}
}

void ASaveTheEarth::BeginPlay()
{
	Super::BeginPlay();

	AActor* PlanetActor = UGameplayStatics::GetActorOfClass(this, APlanet::StaticClass());
	if (PlanetActor)
	{
		PlanetHealthComponent = PlanetActor->FindComponentByClass<UHealthComponent>();
	}
}

void ASaveTheEarth::HandleEnemyBreachedOrbit()
{
	if (bIsGameOver)
	{
		return;
	}

	if (PlanetHealthComponent)
	{
		PlanetHealthComponent->ApplyDamage(EarthDamagePerBreach);
	}


}