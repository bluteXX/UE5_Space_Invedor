#include "SpaceInvaderNormal.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "SpaceInvaderGameState.h"
#include "Planet.h"     
#include "HealthComponent.h"
#include "PlayerShip.h"
#include "EnemyManager.h"

void ASpaceInvaderNormal::GameOver()
{

	if (bIsGameOver)
	{
		return;
	}


	bIsGameOver = true;

	UE_LOG(LogTemp, Warning, TEXT("Game Over"));
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (PC)
	{
		PC->DisableInput(PC);


		APawn* PlayerPawn = PC->GetPawn();
		if (PlayerPawn)
		{
			PlayerPawn->SetActorHiddenInGame(true);
			PlayerPawn->SetActorEnableCollision(false);
		}
	}
	if (ASpaceInvaderGameState* GS = GetGameState<ASpaceInvaderGameState>())
	{
		GS->StopTimer();
	}


	OnGameOverUI();
}

void ASpaceInvaderNormal::GameWon()
{
	if (bIsGameOver)
	{
		return;
	}

	bIsGameOver = true;
	UE_LOG(LogTemp, Warning, TEXT("Game Won"));

	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (PC)
	{

		PC->DisableInput(PC);


		APawn* PlayerPawn = PC->GetPawn();
		if (PlayerPawn)
		{
			PlayerPawn->DisableInput(PC);
		}
	}
	if (ASpaceInvaderGameState* GS = GetGameState<ASpaceInvaderGameState>())
	{
		GS->StopTimer();
	}

	OnGameWonUI();
}

ASpaceInvaderNormal::ASpaceInvaderNormal()
{}



void ASpaceInvaderNormal::BeginPlay()
{
	Super::BeginPlay();

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	BindPlayerHealthDelegate(PlayerPawn);

	AActor* PlanetActor = UGameplayStatics::GetActorOfClass(this, APlanet::StaticClass());
	if (PlanetActor)
	{
		UHealthComponent* PlanetHealth = PlanetActor->FindComponentByClass<UHealthComponent>();
		if (PlanetHealth)
		{
			PlanetHealth->OnDeath.AddDynamic(this, &ASpaceInvaderNormal::OnPlanetDied);
		}
	}

	AActor* ManagerActor = UGameplayStatics::GetActorOfClass(this, AEnemyManager::StaticClass());
	EnemyManagerRef = Cast<AEnemyManager>(ManagerActor);
	if (EnemyManagerRef)
	{
		EnemyManagerRef->OnAllEnemiesDefeated.AddDynamic(this, &ASpaceInvaderNormal::HandleAllEnemiesDefeated);
		EnemyManagerRef->OnEnemyBreachedOrbit.AddDynamic(this, &ASpaceInvaderNormal::HandleEnemyBreachedOrbit);
	}
}

void ASpaceInvaderNormal::HandleAllEnemiesDefeated()
{
	GameWon();
}

void ASpaceInvaderNormal::BindPlayerHealthDelegate(APawn* PlayerPawn)
{
	if (!PlayerPawn)
	{
		return;
	}

	if (UHealthComponent* PlayerHealth = PlayerPawn->FindComponentByClass<UHealthComponent>())
	{
		PlayerHealth->OnDeath.AddDynamic(this, &ASpaceInvaderNormal::OnPlayerDied);
	}
}

void ASpaceInvaderNormal::OnPlayerDied()
{
	UE_LOG(LogTemp, Warning, TEXT("Gracz"));
	GameOver();
}


void ASpaceInvaderNormal::OnPlanetDied()
{
	UE_LOG(LogTemp, Error, TEXT("Planeta"));
	GameOver();
}

void ASpaceInvaderNormal::HandleEnemyBreachedOrbit()
{
	GameOver();
}
