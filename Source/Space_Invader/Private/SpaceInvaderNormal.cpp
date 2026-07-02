#include "SpaceInvaderNormal.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"

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

	
	OnGameWonUI();
}

ASpaceInvaderNormal::ASpaceInvaderNormal()
{
}